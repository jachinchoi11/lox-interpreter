

#ifndef SCANNER_H
#define SCANNER_H
#include <string>
#include <vector>
#include "Token.h"


class Scanner {
    std::string source;
    unsigned int start = 0;
    unsigned int current = 0;
    unsigned int line = 1;
    char current_char;

    void advance();
    bool isAtEnd();
    void scanToken();
    std::vector<Token> tokens;

public:
    Scanner(const std::string& source);
    std::vector<Token> scanTokens();
};
#endif //SCANNER_H
