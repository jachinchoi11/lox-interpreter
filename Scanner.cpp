
#include "Scanner.h"
#include <string>

Scanner::Scanner(const std::string& source) {
    this->source = source;
}

std::vector<Token> Scanner::scanTokens() {
    while (!isAtEnd()) {
        start = current;
        scanToken();
    }
    Token end_of(TokenType::END_OF, TokenType::tokenTypetoString(END_OF), "", line);
    return tokens;
}
void Scanner::scanToken() {
    advance();
    current_char = source[current];

    switch (current_char) {
        case('('):
            addToken
    }
}

void Scanner::advance() {
    current += 1;
}
bool Scanner::isAtEnd() {
    return current >= source.length();
}

void Scanner::addToken(TokenType type) {};






