
#include "TokenType.h"
#include <any>

#ifndef TOKEN_H
#define TOKEN_H

struct Token {
    TokenType type;
    std::string lexeme;
    int line;
    std::any literal;

    std::string toString();

    Token(TokenType type, std::string lexeme, unsigned int line, std::any literal);

};
#endif //TOKEN_H
