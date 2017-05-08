#include "Color.h"

namespace Color {
    float v = 0.0;
    void setColor(const Cairo::RefPtr<Cairo::Context>& cr, TColor color){
        switch(color){
        case WHITE:
            cr->set_source_rgb(1.0, 1.0, 1.0);
            break;
        case BLUE:
            cr->set_source_rgb(0.0, 0.0, 1.0);
            break;
            case LIME:
        case GREEN:
            cr->set_source_rgb(0.0, 1.0, 0.0);
            break;
        case RED:
            cr->set_source_rgb(1.0, 0.0, 0.0);
            break;
        case GREY:
            v = 128.0/255;
            cr->set_source_rgb(v, v, v);
            break;
        case SILVER:
            v = 192.0/255; 
            cr->set_source_rgb(v, v, v);
            break;
        case YELLOW:
            cr->set_source_rgb(1.0, 1.0, 0.0);
            break;
        case AQUA:
        case CIAN:
            cr->set_source_rgb(0.0, 1.0, 1.0);
            break;
        case MARRON:
        case BROWN:
            cr->set_source_rgb(128.0/255, 0.0, 0.0);
            break;
        case PURPLE:
            v = 128.0/255; 
            cr->set_source_rgb(v, 0.0, v);
            break;
        case NAVY:
            cr->set_source_rgb(0.0, 0.0, 128.0/255);
            break;
        case FUCHSIA:
        case PINK:
            cr->set_source_rgb(1.0, 0.0, 1.0);
            break;
        case OLIVE:
            v = 128.0/255; 
            cr->set_source_rgb(v, v, 0.0);
            break;
        case TEAL:
            v = 128.0/255; 
            cr->set_source_rgb(v, v, 0.0);
            break;
        case BLACK:
        default:
            cr->set_source_rgb(0.0, 0.0, 0.0);
        }
    }

    void toRGBArray(TColor color, float rgb[3]){
        switch(color){
        case WHITE:
          rgb[0] = 1.0; rgb[1] = 1.0; rgb[2] = 1.0;
          break;
         case BLUE:
          rgb[0] = 0.0; rgb[1] = 0.0; rgb[2] = 1.0;
          break;
         case GREEN:
          rgb[0] = 0.0; rgb[1] = 128.0/255; rgb[2] = 0.0;
          break;
         case RED:
          rgb[0] = 1.0; rgb[1] = 0.0; rgb[2] = 0.0;
          break;
         case GREY:
          rgb[0] = 128.0/255; rgb[1] = 128.0/255; rgb[2] = 128.0/255;
          break;
         case SILVER:
          rgb[0] = 192.0/255; rgb[1] = 192.0/255; rgb[2] = 192.0/255;
          break;
         case YELLOW:
          rgb[0] = 1.0; rgb[1] = 1.0; rgb[2] = 0.0;
          break;
         case LIME:
          rgb[0] = 0.0; rgb[1] = 1.0; rgb[2] = 0.0;
          break;
         case AQUA:
         case CIAN:
          rgb[0] = 0.0; rgb[1] = 1.0; rgb[2] = 1.0;
          break;
         case MARRON:
         case BROWN:
          rgb[0] = 128.0/255; rgb[1] = 0.0; rgb[2] = 0.0;
          break;
         case PURPLE:
          rgb[0] = 128.0/255; rgb[1] = 0.0; rgb[2] = 128.0/255;
          break;
         case NAVY:
          rgb[0] = 0.0; rgb[1] = 0.0; rgb[2] = 128.0/255;
          break;
         case FUCHSIA:
         case PINK:
          rgb[0] = 1.0; rgb[1] = 0.0; rgb[2] = 1.0;
          break;
         case OLIVE:
          rgb[0] = 128.0/255; rgb[1] = 128.0/255; rgb[2] = 0.0;
          break;
         case TEAL:
          rgb[0] = 0.0; rgb[1] = 128.0/255; rgb[2] = 128.0/255;
          break;
        case BLACK:
        default:
         rgb[0] = 0.0; rgb[1] = 0.0; rgb[2] = 0.0;
        }
    }

    void toRGBArrayLighter(TColor color, float rgb[3]){
        toRGBArray(color, rgb);
        rgb[0] += rgb[0] + 0.25 > 1.0 ? 0 : 0.25; 
        rgb[1] += rgb[1] + 0.25 > 1.0 ? 0 : 0.25; 
        rgb[2] += rgb[2] + 0.25 > 1.0 ? 0 : 0.25; 
    }

    void toRGBArrayDarker(TColor color, float rgb[3]){
        toRGBArray(color, rgb);
        rgb[0] -= rgb[0] - 0.25 < 0.0 ? 0 : 0.25; 
        rgb[1] -= rgb[1] - 0.25 < 0.0 ? 0 : 0.25; 
        rgb[2] -= rgb[2] - 0.25 < 0.0 ? 0 : 0.25; 
    }

    TColor stringToTColor(string color){
        if(color == "white"){ return WHITE; }
        else if(color == "black"){ return BLACK; }
        else if(color == "blue"){ return BLUE; }
        else if(color == "green"){ return GREEN; }
        else if(color == "red"){ return RED; }
        else if(color == "grey"){ return GREY; }
        else if(color == "silver"){ return SILVER; }
        else if(color == "yellow"){ return YELLOW; }
        else if(color == "lime"){ return LIME; }
        else if(color == "aqua" || color == "cian"){ return CIAN; }
        else if(color == "marron" || color == "brown"){ return BROWN; }
        else if(color == "purple"){ return PURPLE; }
        else if(color == "navy"){ return NAVY; }
        else if(color == "fuchsia" || color == "pink"){ return PINK; }
        else if(color == "olive"){ return OLIVE; }
        else if(color == "teal"){ return TEAL; }
        else{ return BLACK; }
    }

    string TColorToString(TColor color){
        if(color == WHITE){ return "white"; }
        else if(color == BLACK){ return "black"; }
        else if(color == BLUE){ return "blue"; }
        else if(color == GREEN){ return "green"; }
        else if(color == RED){ return "red"; }
        else if(color == GREY){ return "grey"; }
        else if(color == SILVER){ return "silver"; }
        else if(color == YELLOW){ return "yellow"; }
        else if(color == LIME){ return "lime"; }
        else if(color == AQUA || color == CIAN){ return "cian"; }
        else if(color == MARRON || color == BROWN){ return "brown"; }
        else if(color == PURPLE){ return "purple"; }
        else if(color == NAVY){ return "navy"; }
        else if(color == FUCHSIA || color == PINK){ return "pink"; }
        else if(color == OLIVE){ return "olive"; }
        else if(color == TEAL){ return "teal"; }
        else{ return "black"; }
    }
}