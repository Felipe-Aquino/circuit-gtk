#ifndef __REPORT_H_
#define __REPORT_H_

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

namespace report {
    namespace {
        static stringstream formater;
    }

    void report(string msg);
    void warn(string msg);
    void error(string msg);
    void exception(string msg);
    void exception(char* msg);

    string format(const char* fmt);

    template<typename T, typename... Targs>
    string format(const char* fmt, T value, Targs... Fargs) {
        string result = "";
        formater.str("");
        for ( ; *fmt != '\0'; fmt++ ) {
            if (*fmt == '%') {
                formater << value;
                result = formater.str();
                result += format(fmt+1, Fargs...);
                return result;
            }
            formater << *fmt;
        }
        return formater.str();
    }
}

#endif // __REPORT_H_
