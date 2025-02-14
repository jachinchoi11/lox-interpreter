#include "Token.h"
#include <iostream>
#include "TokenType.h"

Token::Token(TokenType type, std::string lexeme, unsigned int line): type(type), lexeme(lexeme), line(line) {};

std::string Token::toString(TokenType tokenType, std::string lexeme){
    std::string output = "Token type: " + tokenTypeToString(tokenType) + lexeme + std::to_string(line);
    return output;
}



