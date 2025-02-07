
#include "Token.h"
#include <iostream>
#include "TokenType.h"

Token::Token(TokenType type, std::string &lexeme, std::any literal, int line): type(type), lexeme(lexeme), literal(literal), line(line) {};

std::string Token::toString(TokenType tokenType, std::string& lexeme){
    std::string output = "Token type: " + TokenType::tokenTypetoString(type) + lexeme +  line;
    return output;
}



