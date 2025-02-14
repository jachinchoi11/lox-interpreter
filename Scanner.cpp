
#include "Scanner.h"
#include <string>
#include "TokenType.h"
#include "Error.h"



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
    line += 1;
    return tokens;
}

void Scanner::scanToken() {
    advance();
    current_char = source[current];

    switch (current_char) {
        // one character tokens
        case '(':
            return createToken(TokenType::LEFT_PAREN);
        case ')':
            return createToken(TokenType::RIGHT_PAREN);
        case '{':
            return createToken(TokenType::LEFT_BRACE);
        case '}':
            return createToken(TokenType::RIGHT_BRACE);
        case ',':
            return createToken(TokenType::COMMA);
        case '.':
            return createToken(TokenType::DOT);
        case ';':
            return createToken(TokenType::SEMICOLON);
        case '*':
            return createToken(TokenType::STAR);
        // one character tokens that can be ttwo characters - !=, ==, <=, >=

        case '!':
            if (nextToken('=')) {
                return createToken(TokenType::BANG_EQUAL);
            }
            return createToken(TokenType::BANG);
        case '=':
            if (nextToken('=')) {
                return createToken(TokenType::EQUAL_EQUAL);
            }
            return createToken(TokenType::EQUAL);
        case '<':
            if (nextToken('=')) {
                return createToken(TokenType::GREATER_EQUAL);
            }
            return createToken(TokenType::GREATER);
        case '>':
            if (nextToken('=')) {
                return createToken(TokenType::LESS_EQUAL);
            }
            return createToken(TokenType::LESS);
        case '/':
            if (nextToken('/')) {
                while (!nextToken('\n') && !isAtEnd()) {
                    advance();
                }
                break;
            }
            return createToken(TokenType::SLASH);
        case ' ':
        case '\t':
            break;
        case '\n':
        case '\r':
        case '"':
            scanString();
            break;

        default:
            if (isdigit(current_char)) {
                scanNumber();
                break;
            }
            else {
                std::cerr << "Scanner error: unexpected character '" << current_char << "'\n";
            }
    }
}

bool Scanner::nextToken(char expected) {
    if (isAtEnd()) {
        return false;
    }
    if (source[current + 1] != expected) {
        return false;
    }
    current += 1;
    return true;

}
void Scanner::advance() {
    current += 1;
}

bool Scanner::isAtEnd() {
    return current >= source.length();
}

void Scanner::createToken(TokenType type) {
    addToken(type);
};
void Scanner::addToken(TokenType type) {
    std::string curr_text = source.substr(start, current - start);
    // substr takes where it starts, and how long it is
    tokens.push_back(Token(type, curr_text, line));
}

void Scanner::scanString() {
    while (peek() != '\n' and !isAtEnd()) {
        if (peek() == '\n') {
            line += 1;
        }
        advance();
    }
    std::string string_literal = source.substr(start + 1, current - start - 1);
    createToken(STRING);
}
void Scanner::scanNumber() {
    while (isdigit(peek())) {
        advance();
    }
    std::string number_literal = source.substr(start, current - start);
    createToken(NUMBER);
}
char Scanner::peek() const {
    return source[current];
}






