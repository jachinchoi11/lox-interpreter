

#ifndef ERROR_H
#define ERROR_H
#include <iostream>

class Error {
    static void error(int line, std::string message);
    static void report(int line, std::string location, std::string message);
public:
    static bool hasError;
};
#endif //ERROR_H
