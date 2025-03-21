#include "Token.h"
#include <iostream>
#include "TokenType.h"

Token::Token(TokenType type, std::string lexeme, unsigned int line, std::any literal): type(type), lexeme(lexeme), line(line), literal(literal) {};

std::string Token::toString() {
    std::string output = tokenTypeToString(type) + " ";

    if (literal.has_value()) {
        if (literal.type() == typeid(std::string)) {
            output += std::any_cast<std::string>(literal);
        } else if (literal.type() == typeid(int)) {
            output += std::to_string(std::any_cast<int>(literal));
        } else {
            output += "[Unsupported Type]";
        }
    } else {
        output += "[No Literal]";
    }

    output += " Lexeme: " + lexeme + "  Line: " + std::to_string(line);
    return output;
}




