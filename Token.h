
#include "TokenType.h"
#include <any>

#ifndef TOKEN_H
#define TOKEN_H

struct Token {
    TokenType type;
    std::string lexeme;
    std::any literal;
    int line;

    Token(TokenType type, std::string& lexeme, std::any literal, int line);
    std::string toString(TokenType tokenType, std::string& lexeme);

};
#endif //TOKEN_H
