#include "report.h"

namespace report {
    namespace {
        template <typename Enumeration>
        auto get(Enumeration const value) -> typename underlying_type<Enumeration>::type {
            return static_cast<typename underlying_type<Enumeration>::type>(value);
        }

        enum class fg {
            black   = 30,
            red     = 31,
            green   = 32,
            yellow  = 33,
            blue    = 34,
            magenta = 35,
            cyan    = 36,
            white   = 37
        };

        enum class bg {
            none    = -1,
            black   = 40,
            red     = 41,
            green   = 42,
            yellow  = 43,
            blue    = 44,
            magenta = 45,
            cyan    = 46,
            white   = 47
        };

        enum style {
            reset        = 0,
            bold         = 1,
            underline    = 4,
            inverse      = 7,
            bold_off     = 21,
            underline_off= 24,
            inverse_off  = 27
        };

        const string endcode = "\033[0m";

        string mkcode(style s, fg fgcolor, bg bgcolor = bg::none) {
            stringstream ss;
            ss << "\033[" << s << ";" << get(fgcolor);
            if(bgcolor != bg::none) ss << ";" << get(bgcolor) << "m";
            else ss << "m";
            return ss.str();
        }
    }

    void report(string msg) {
        cout << mkcode(bold, fg::blue) << "REPORT" << endcode;
        cout << ": " << msg << endl;
    }

    void warn(string msg) {
        cout << mkcode(bold, fg::yellow) << "WARNING" << endcode;
        cout << ": " << msg << endl;
    }

    void error(string msg) {
        cout << mkcode(bold, fg::red) << "ERROR" << endcode;
        cout << ": " << msg << endl;
    }

    void exception(string msg) {
        cout << mkcode(bold, fg::magenta) << "EXCEPTION" << endcode;
        cout << ": " << msg << endl;
    }

    void exception(char* msg) {
        cout << mkcode(bold, fg::magenta) << "EXCEPTION" << endcode;
        cout << ": " << msg << endl;
    }

    string format(const char* fmt) {
        formater.str("");
        formater << fmt;
        return formater.str();
    }
}
