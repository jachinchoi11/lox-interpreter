

#ifndef SCANNER_H
#define SCANNER_H
#include <string>
#include <vector>
#include "Token.h"
#include "TokenType.h"


class Scanner {
    std::string source;
    int start = 0;
    int current = 0;
    int line = 1;
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
