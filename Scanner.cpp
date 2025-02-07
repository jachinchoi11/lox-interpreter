
#include "Scanner.h"
#include <string>
#include "TokenType.h"

Scanner::Scanner(const std::string& source) {
    this->source = source;
}

std::vector<Token> Scanner::scanTokens() {
    while (!isAtEnd()) {
        start = current;
        scanToken();
    }
    Token end_of(TokenType::END_OF, tokenTypeToString(END_OF), line);
    tokens.push_back(end_of);
    return tokens;
}
// void Scanner::scanToken() {
//     advance();
//     current_char = source[current];
//
//     switch (current_char) {
//         case('('):
//             addToken
//     }
// }

void Scanner::advance() {
    current += 1;
}
bool Scanner::isAtEnd() {
    return current >= source.length();
}

// void Scanner::addToken(TokenType type) {};
//





