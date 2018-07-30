#include "fast_gui.h"
#include <fstream>
#include <string>
#include <map>

namespace fst {
    /* Types */
    typedef enum colors {
        DEFAULT,
        HALF_DEFAULT,
        WHITE,
        BLACK,
        HOVER,
        DARK1
    } Colors;

    typedef enum drawFlags {
        DRAW_FLAGS_FILL,
        DRAW_FLAGS_STROKE
    } DrawFlags;

    struct Rect {
        DrawFlags flag;
        float x, y, w, h;
        Colors color;
    };

    struct Txt {
        float x, y;
        std::string text;
        Colors color;
    };

    struct EntryInfo {
        bool editing = false;
        int id_editing = -1;
        std::string text;
    };

    struct WindoW {
        int x = 10, y = 10;
        int width = 200, height = 300;
        int yscroll = 0, xscroll = 0;
        int font_size = 12;
        bool moving = false;
        bool resizing = false;
        Cairo::RefPtr<Cairo::Context> cr;
        Cairo::RefPtr<Cairo::Surface> surf;
        std::vector<Rect*> rects;
        std::vector<Txt*> txts;
    };

    struct Frame {
        int last_xoff = 0, last_yoff = 0;
        int xpad = 4, ypad = 1;
        int xmargin = 4, ymargin = 5;
        int count = 0;
        EntryInfo info;
        std::map<int, bool> expand_status;
        std::string symbols = " !@%#$&*-+:;?~{}[]().,/\\";

        int x = 10, y = 0;
        int xoffset = 0, yoffset = 0;
        int line_height = 15, line_width = 200;

        bool ignore = false;
        std::vector<bool> ignore_queue;
        bool closed_expander = false;
        int expand_level = 1;

        void copy(Frame& other) {
            x = other.x;
            y = other.y;
            xoffset = other.xoffset;
            yoffset = other.yoffset;
            line_height = other.line_height;
            line_width = other.line_width;
            closed_expander = false;
            expand_level = other.expand_level;
            ignore = false;
            ignore_queue.clear();
            count = 0;
        }
    };

    struct Mouse {
        bool pressed = false;
        int x = 0, y = 0;
        int dx = 0, dy = 0;
    };

    /* Static objects */
    static Mouse mouse;
    static Frame frame;
    static Frame frame_start;
    static WindoW wind;

    /* Declarations */
    static void
    round_rect(const Cairo::RefPtr<Cairo::Context>& cr, bool title = true);

    static void
    addText(float x, float y, std::string text, Colors c = WHITE);

    static void
    addRect(float x, float y, float w, float h, Colors c = DEFAULT, DrawFlags f = DRAW_FLAGS_FILL);

    static int
    txtWidth(std::string txt);

    /* Definitions */

    void addRect(float x, float y, float w, float h, Colors c, DrawFlags f) {
        auto r = new Rect();
        r->x = x;
        r->y = y;
        r->w = w;
        r->h = h;
        r->flag = f;
        r->color = c;
        wind.rects.push_back(r);
    }

    void addText(float x, float y, std::string text, Colors c) {
        auto r = new Txt();
        r->x = x;
        r->y = y;
        r->text = text;
        r->color = c;
        wind.txts.push_back(r);
    }

    int txtWidth(std::string txt) {
        Cairo::TextExtents ext;
        wind.cr->get_text_extents(txt, ext);
        return ext.width;
    }

    int txtAdvance(std::string txt) {
        Cairo::TextExtents ext;
        wind.cr->get_text_extents(txt, ext);
        return ext.x_advance;
    }

    bool mouse_inside_rect(int x, int y, int w, int h) {
        return mouse.x >= x && mouse.x <= x + w &&
               mouse.y >= y && mouse.y <= y + h;
    }

    void pre_init() {
        std::ifstream file("init.gui");
        if(file.is_open()) {
            std::string line;
            while(std::getline(file, line)) {
                int pos = line.find(' ');
                if(!line.compare(0, pos, "x"))
                    wind.x = stoi(line.substr(pos + 1));
                else if(!line.compare(0, pos, "y"))
                    wind.y = stoi(line.substr(pos + 1));
                else if(!line.compare(0, pos, "width"))
                    wind.width = stoi(line.substr(pos + 1));
                else if(!line.compare(0, pos, "height"))
                    wind.height = stoi(line.substr(pos + 1));
            }
        }
        file.close();
    }

    void end() {
        std::ofstream file("init.gui", std::ios::out | std::ios::trunc);
        if(file.is_open()) {
            file << "x " << wind.x << std::endl;
            file << "y " << wind.y << std::endl;
            file << "width " << wind.width << std::endl;
            file << "height " << wind.height << std::endl;
        }
        file.close();
    }

    void init(const Cairo::RefPtr<Cairo::Context>& cr) {
        frame.copy(frame_start);
        frame.y += frame.line_height + wind.width / 20.0;

        double x, y;
        cr->get_target()->get_device_offset(x, y);

        wind.surf = Cairo::Surface::create(cr->get_target(), -x + wind.x, -y + wind.y, wind.width, wind.height);
        wind.cr = Cairo::Context::create(wind.surf);

        wind.cr->set_font_size(wind.font_size);
        wind.cr->select_font_face("Inconsolada",
                                  Cairo::FontSlant::FONT_SLANT_NORMAL,
                                  Cairo::FontWeight::FONT_WEIGHT_NORMAL);
    }

    void render(const Cairo::RefPtr<Cairo::Context>& cr) {

        round_rect(wind.cr);

        Cairo::RefPtr<Cairo::Surface> frame_surf = Cairo::Surface::create(wind.cr->get_target(), frame.x, frame.y, wind.width - frame.x, wind.height - frame.y);
        Cairo::RefPtr<Cairo::Context> frame_cr = Cairo::Context::create(frame_surf);

        for(auto r: wind.rects) {
            switch(r->color) {
            case DEFAULT:
                frame_cr->set_source_rgb(41/255.0, 74/255.0, 122/255.0);
                break;
            case HALF_DEFAULT:
                frame_cr->set_source_rgba(41/255.0, 74/255.0, 122/255.0, 0.5);
                break;
            case WHITE:
                frame_cr->set_source_rgb(1, 1, 1);
                break;
            case BLACK:
                frame_cr->set_source_rgb(0, 0, 0);
                break;
            case HOVER:
                frame_cr->set_source_rgb(70/255.0, 150/255.0, 180/255.0);
                break;
            case DARK1:
                frame_cr->set_source_rgb(20/255.0, 37/255.0, 61/255.0);
                break;
            default:
                frame_cr->set_source_rgb(0, 0, 0);
                break;
            }

            frame_cr->rectangle(r->x, r->y, r->w, r->h);
            if(r->flag == DRAW_FLAGS_FILL) {
                frame_cr->fill();
            } else if(r->flag == DRAW_FLAGS_STROKE) {
                frame_cr->set_line_width(1);
                frame_cr->stroke();
            }
            delete r;
        }

        frame_cr->select_font_face("Inconsolada",
                                   Cairo::FontSlant::FONT_SLANT_NORMAL,
                                   Cairo::FontWeight::FONT_WEIGHT_NORMAL);
        frame_cr->set_source_rgb(1, 1, 1);
        frame_cr->set_font_size(wind.font_size);
        for(auto t: wind.txts) {
            frame_cr->move_to(t->x, t->y);
            frame_cr->show_text(t->text);
            delete t;
        }

        wind.rects.clear();
        wind.txts.clear();
    }

    void SameLine(void) {
        frame.xoffset = frame.last_xoff;
        frame.yoffset = frame.last_yoff;
    }

    void Text(std::string txt) {
        int x = frame.xoffset;
        int y = -wind.yscroll + frame.yoffset + frame.line_height + frame.ymargin;

        if(frame.ignore) return;

        addText(x, y, txt);

        frame.last_yoff = frame.yoffset;
        frame.yoffset  += frame.line_height + frame.ymargin;

        frame.last_xoff = frame.xoffset + txtWidth(txt) + frame.xmargin;
        frame.xoffset   = frame_start.xoffset;
    }

    bool Button(std::string txt) {
        //float step = txtWidth("W");
        float x = frame.xoffset;
        float y = - wind.yscroll + frame.yoffset + frame.line_height + 2*frame.ypad + frame.ymargin;
        float box_w = txtAdvance(txt) + 2*frame.xpad, box_h = frame.line_height + 2*frame.ypad;

        bool pressed = false;
        Colors color = DEFAULT;

        if(frame.ignore) return false;

        if(mouse_inside_rect(x + wind.x + frame.x, y + wind.y + frame.y - box_h, box_w, box_h))
        {
            if(mouse.pressed) {
                pressed = true;
                color = BLACK;
            }
            else
                color = HOVER;
        }

        //std::cout << txtWidth(txt) << ", " << txtAdvance(txt) << ", " << txt.size()*step << std::endl;
        addRect(x, y - box_h + frame.ypad, box_w, box_h, color);
        addText(x + frame.xpad, y - (box_h - wind.font_size) / 2, txt);

        frame.last_yoff = frame.yoffset;
        frame.yoffset += frame.line_height + frame.ymargin;

        frame.last_xoff = frame.xoffset + box_w + frame.xmargin;
        frame.xoffset = frame_start.xoffset;

        return pressed;
    }

    void Spin(float &v, float step) {
        float w = txtWidth("00000000000");
        int x = frame.xoffset;
        int y = -wind.yscroll + frame.yoffset + frame.line_height + 2*frame.ypad + frame.ymargin;
        int box_w = w + 2*frame.xpad, box_h = frame.line_height + 2*frame.ypad;

        if(frame.ignore) return;

        addRect(x, y - box_h + frame.ypad, box_w, box_h, HALF_DEFAULT);

        frame.xoffset += box_w + frame.xpad;
        if(Button("-")) {
            v -= step;
        }
        SameLine();
        if(Button("+")) {
            v += step;
        }
        SameLine();

        w = w / 2;
        std::string number = std::to_string((float)v);
        number.erase(number.size() - 3);
        addText(x + frame.xpad + w - txtWidth(number)/2 , y - (box_h - wind.font_size) / 2, number);

        frame.yoffset += frame.line_height + frame.ymargin;
        frame.xoffset = frame_start.xoffset;
    }

    void Toggle(std::string txt, bool &v) {
        int x = frame.xoffset + 1;
        int y = -wind.yscroll + frame.yoffset + frame.line_height + 2*frame.ypad + frame.ymargin;
        int base_x = x + wind.x + frame.x, base_y = y + wind.y + frame.y - frame.line_height + frame.ypad;
        Colors color = HALF_DEFAULT;

        if(frame.ignore) return;

        if(mouse.pressed) {
            if(mouse_inside_rect(base_x, base_y, frame.line_height, frame.line_height - frame.ypad)) {
                v = !v;
            }
        }

        if(v) color = WHITE;

        addRect(x, y - frame.line_height + frame.ypad, frame.line_height, frame.line_height, color);
        addRect(x, y - frame.line_height + frame.ypad, frame.line_height, frame.line_height, BLACK, DRAW_FLAGS_STROKE);

        addText(x + frame.line_height + frame.xpad, y, txt);

        frame.yoffset  += frame.line_height + frame.ymargin;
        frame.last_xoff = frame.xoffset + txtWidth(txt) + 2*frame.xmargin;
        frame.xoffset   = frame_start.xoffset;
    }

    void Slider(float &v, float min, float max) {
        int x = frame.xoffset;
        int y = -wind.yscroll + frame.yoffset + frame.line_height + 2*frame.ypad + frame.ymargin;
        int box_w = 110, box_h = frame.line_height + 2*frame.ypad;
        float frac = v / (max - min);
        float new_x = x + frac*(box_w - 10);

        if(frame.ignore) return;

        if(mouse.pressed) {
            if(mouse_inside_rect(x + wind.x + frame.x, y + wind.y + frame.y - box_h, box_w, box_h)) {
                frac = (mouse.x - (wind.x + frame.x + x))*1.0 / (box_w - 10.0);
                v = min + (max - min)*frac;
                new_x = mouse.x - (wind.x + frame.x + x);
                if(frac > 1.0) new_x = box_w - 10;
            }
        }

        if(v > max) v = max;
        else if(v < min) v = min;

        addRect(x    , y - box_h + frame.ypad, box_w, box_h, HALF_DEFAULT);
        addRect(new_x, y - box_h + frame.ypad, 10   , box_h, DARK1);

        std::string number = std::to_string(v);
        number.erase(number.size() - 3);
        addText(x + box_w / 2 - txtWidth(number)/2, y - (box_h - wind.font_size) / 2, number);

        frame.last_yoff = frame.yoffset;
        frame.yoffset += frame.line_height + frame.ymargin;

        frame.last_xoff = frame.xoffset + box_w + frame.xmargin;
        frame.xoffset = frame_start.xoffset;
    }

    void TextEntry(std::string &text) {
        if(frame.ignore) return;

        int id = frame.count++;

        int x = frame.xoffset;
        int y = - wind.yscroll + frame.yoffset + frame.line_height + 2*frame.ypad + frame.ymargin;
        int box_w = 110;
        int box_h = frame.line_height + 2*frame.ypad;

        if(mouse.pressed) {
            if(mouse_inside_rect(x + wind.x + frame.x, y + wind.y + frame.y - box_h, box_w, box_h)) {
                frame.info.id_editing = id;
                frame.info.editing = true;
            } else if(frame.info.id_editing == id) {
                frame.info.id_editing = -1;
                frame.info.editing = false;
                frame.info.text = "";
            }
        }

        addRect(x, y - box_h + frame.ypad, box_w, box_h, HALF_DEFAULT);

        std::string txt = "";
        if (frame.info.id_editing == id) {

            txt = frame.info.text;
            if(!frame.info.editing) {
                frame.info.id_editing = -1;
                frame.info.text = "";
                text = txt;
            }
            else {
                //int step  = txtWidth("a");
                int width = txtAdvance(txt); //txt.size()*step;

                while(width >= box_w) {
                    txt.erase();
                    width = txtAdvance(txt); //txt.size()*step;
                }

                addRect(x + width + 1, y - frame.line_height , 2    , frame.line_height, DARK1);
                addRect(x            , y - box_h + frame.ypad, box_w, box_h            , DARK1, DRAW_FLAGS_STROKE);
                addText(x            , y - (box_h - wind.font_size) / 2, txt);
            }
        }
        else {
            txt   = text;
            //int step  = txtWidth("a");
            int width = txtAdvance(txt); //txt.size()*step;

            while(width >= box_w) {
                txt.pop_back();
                width = txtAdvance(txt); //txt.size()*step;
            }

            addText(x, y - (box_h - wind.font_size) / 2, txt);
        }

        frame.last_yoff = frame.yoffset;
        frame.yoffset   += frame.line_height + frame.ymargin;

        frame.last_xoff = frame.xoffset + box_w + frame.xmargin;
        frame.xoffset   = frame_start.xoffset;
    }

    void BeginExpander(std::string txt) {
        frame.ignore_queue.push_back(frame.ignore);

        int id = frame.count++;
        bool expanded = false;
        if(frame.expand_status.find(id) != frame.expand_status.end())
            expanded = frame.expand_status[id];
        else
            frame.expand_status[id] = false;

        frame.closed_expander = false;
        frame.expand_level += 1;

        if(frame.ignore) return;

        int x = frame.xoffset;
        int y = - wind.yscroll + frame.yoffset + frame.line_height + 2*frame.ypad + frame.ymargin;
        int base_x = x + wind.x + frame.x;
        int base_y = y + wind.y + frame.y - frame.line_height + frame.ypad;
        int w = wind.width - frame.x*2*(frame.expand_level - 1) - 10;
        Colors color = DEFAULT;

        if(mouse_inside_rect(base_x, base_y, w, frame.line_height - frame.ypad))
            if(mouse.pressed) {
                expanded = !expanded;
                frame.expand_status[id] = expanded;
                color = BLACK;
            }

        frame.ignore = !expanded;

        addRect(x, y - frame.line_height + frame.ypad, w, frame.line_height + frame.ypad, color);

        if(expanded)
            txt = "[-] " + txt;
        else
            txt = "[+] " + txt;

        addText(x, y, txt);

        frame.yoffset  += frame.line_height + frame.ymargin;
        frame.last_xoff = frame.xoffset + w;

        frame_start.xoffset += 15;
        frame.xoffset   = frame_start.xoffset;
    }

    void EndExpander(void) {
        frame.ignore = false;
        if(!frame.ignore_queue.empty()) {
            frame.ignore = frame.ignore_queue.back();
            frame.ignore_queue.pop_back();
        }
        if(!frame.ignore) {
            frame_start.xoffset -= 15;
            frame.xoffset   = frame_start.xoffset;
        }

        frame.expand_level -= 1;
        if(frame.expand_level == 1)
            frame.closed_expander = true;
    }

    int vscroll_bar(const Cairo::RefPtr<Cairo::Context> &cr, int x, int y, int scroll, int frame_height, int total_height) {

        if(frame_height >= total_height || frame_height == 0 || total_height == 0)
            return scroll;

        if(mouse.pressed) {
            if(mouse_inside_rect(x + wind.x, wind.y + y, 10, frame_height))
                scroll += mouse.dy;
        }

        int bar_size = frame_height*frame_height / total_height;
        int real_scroll = scroll*frame_height / total_height;
        if(real_scroll < 0) {
            real_scroll = 0;
            scroll = 0;
        }
        else if(real_scroll + bar_size > frame_height) {
            real_scroll = frame_height - bar_size;
            scroll = real_scroll*total_height / frame_height;
        }

        cr->set_source_rgb(41/255.0, 74/255.0, 122/255.0);
        cr->rectangle(x, y, 8, frame_height);
        cr->fill();
        cr->set_source_rgb(0, 0, 0);
        cr->rectangle(x + 1, y + real_scroll, 8, bar_size);
        cr->fill();

        return scroll;
    }

    void resizer(const Cairo::RefPtr<Cairo::Context> &cr, double width, double height, double radius) {
        double degrees = 3.1416926 / 180.0;

        if(mouse.pressed) {
            if(mouse.x >= wind.x + width - radius - 10 && mouse.x <= wind.x + width) {
                int y = height - (mouse.x - wind.x - width + radius + 10);
                if(mouse.y <= wind.y + height && mouse.y >= wind.y + y)
                    wind.resizing = true;
            }
        } else {
            wind.resizing = false;
        }

        if(wind.resizing) {
            wind.width  += mouse.dx;
            wind.height += mouse.dy;
        }
        cr->set_source_rgb(41/255.0, 74/255.0, 122/255.0);
        cr->begin_new_sub_path();

        cr->move_to(width, height - 10 - radius);
        cr->line_to(width, height - radius);
        cr->arc(width - radius, height - radius, radius, 0 * degrees  , 90 * degrees);
        cr->line_to(width - radius - 10, height);

        cr->close_path();
        cr->fill();
    }

    void round_rect(const Cairo::RefPtr<Cairo::Context>& cr, bool title) {
        double width = wind.width, height = wind.height;
        double aspect  = height / width;     /* aspect ratio */
        double corner_radius = height / 20.0;   /* and corner curvature radius */

        double radius = corner_radius / aspect;
        double degrees = 3.1416926 / 180.0;

        if(!wind.moving && mouse.pressed && title) {
            if(mouse_inside_rect(wind.x, wind.y, wind.width, frame.line_height + radius / 2)) {
                wind.moving = true;
            }
        } else if(!mouse.pressed){
            wind.moving = false;
        }

        if(wind.moving) {
            wind.x += mouse.dx;
            wind.y += mouse.dy;
        }

        cr->set_source_rgba(0.0, 0.0, 0.0, 0.6);
        cr->begin_new_sub_path();
        cr->arc(width - radius, radius         , radius, -90 * degrees, 0 * degrees);
        cr->arc(width - radius, height - radius, radius, 0 * degrees  , 90 * degrees);
        cr->arc(radius        , height - radius, radius, 90 * degrees , 180 * degrees);
        cr->arc(radius        , radius         , radius, 180 * degrees, 270 * degrees);
        cr->close_path();
        cr->fill();

        if(title) {
            cr->set_source_rgb(41/255.0, 74/255.0, 122/255.0);
            cr->begin_new_sub_path();
            cr->arc(radius        , radius, radius, 180 * degrees, 270 * degrees);
            cr->arc(width - radius, radius, radius, -90 * degrees, 0 * degrees);

            cr->line_to(width, radius + frame.line_height);
            cr->line_to(0    , radius + frame.line_height);
            cr->close_path();
            cr->fill();

            frame.y = frame_start.y + frame.line_height + radius;
            cr->set_font_size(wind.font_size);
            cr->set_source_rgb(1.0, 1.0, 1.0);
            cr->move_to(frame.x, frame.y - radius / 2);
            cr->show_text("Debug");
        }

        wind.yscroll = vscroll_bar(cr, wind.width - frame.x, frame.y + 2, wind.yscroll, wind.height - frame.y - radius, frame.yoffset);
        resizer(cr, width, height, radius);
    }

    void mouse_press(GdkEventButton* event) {
        mouse.dx = event->x - mouse.x;
        mouse.dy = event->y - mouse.y;
        mouse.x = event->x;
        mouse.y = event->y;

        if((event->type == GDK_BUTTON_PRESS) && (event->button == 1)) {
            mouse.pressed = true;
        }
    }

    void mouse_release(GdkEventButton* event) {
        mouse.dx = event->x - mouse.x;
        mouse.dy = event->y - mouse.y;
        mouse.x = event->x;
        mouse.y = event->y;

        mouse.pressed = false;
    }

    void mouse_move(GdkEventMotion* event) {
        mouse.dx = event->x - mouse.x;
        mouse.dy = event->y - mouse.y;
        mouse.x = event->x;
        mouse.y = event->y;
    }

    bool key_event(GdkEventKey* event) {
        auto key = event->keyval;

        if(key == GDK_KEY_Return)
            frame.info.editing = false;
        else if(key == GDK_KEY_BackSpace) {
            //std::cout << "char " << key << std::endl;
            if(!frame.info.text.empty())
                frame.info.text.pop_back();
        }
        else if(frame.info.editing) {
            char c = char(key);
            if(isalnum(c) || frame.symbols.find(c) >= 0)
                frame.info.text += c;
        }

        return frame.info.editing;
    }
}
