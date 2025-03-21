
#include "Scanner.h"
#include <string>
#include "TokenType.h"
#include "Error.h"
#include <map>

std::map<std::string, TokenType> Scanner::possible_keywords = {
    {"and", TokenType::AND},
    {"class", TokenType::CLASS},
    {"else", TokenType::ELSE},
    {"fun", TokenType::FUN},
    {"for", TokenType::FOR},
    {"if", TokenType::IF},
    {"nil", TokenType::NIL},
    {"or", TokenType::OR},
    {"print", TokenType::PRINT},
    {"return", TokenType::RETURN},
    {"super", TokenType::SUPER},
    {"this", TokenType::THIS},
    {"true", TokenType::TRUE},
    {"false", TokenType::FALSE},
    {"var", TokenType::VAR},
    {"while", TokenType::WHILE},
};

Scanner::Scanner(const std::string& source) {
    this->source = source;
}

std::vector<Token> Scanner::scanTokens() {
    while (!isAtEnd()) {
        start = current;
        scanToken();
    }
    Token end_of(TokenType::END_OF, tokenTypeToString(END_OF), line, std::any(std::string("")));
    tokens.push_back(end_of);
    line += 1;
    return tokens;
}

void Scanner::scanToken() {
    start = current;
    current_char = source[current];
    advance();
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
        case '+':
            return createToken(TokenType::PLUS);
        case '-':
            return createToken(TokenType::MINUS);
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
        case '>':
            if (nextToken('=')) {
                return createToken(TokenType::GREATER_EQUAL);
            }
            return createToken(TokenType::GREATER);
        case '<':
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
            return scanString();
        default:
            if (isdigit(current_char)) {
                return scanNumber();
            }
            else if (isalpha(current_char) || current_char ==  '_') {
                return scanIdentifier();
            }
            else {
                std::cerr << "Scanner error: unexpected character '" << current_char << "'\n";
                return;
            }
    }
}

void Scanner::scanIdentifier() {
    while (isalnum(peek())) {
        advance();
    }

    std::string potential_identifier = source.substr(start, current - start);

    if (possible_keywords.count(potential_identifier) > 0) {
        addToken(possible_keywords[potential_identifier]);
    } else {
        addToken(TokenType::IDENTIFIER);
    }
}

bool Scanner::nextToken(char expected) {
    if (isAtEnd()) {
        return false;
    }
    if (source[current] != expected) {
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
    tokens.push_back(Token(type, curr_text, line, std::any(std::string(""))));
}
void Scanner::addLiteral(TokenType type, std::any value) {
    std::string curr_text = source.substr(start, current - start);
    // substr takes where it starts, and how long it is
    tokens.push_back(Token(type, curr_text, line, value));
}

void Scanner::scanString() {
    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\n') {
            line += 1;
        }
        advance();
    }

    if (isAtEnd()) {
        std::cerr << "Scanner error: Unterminated string.\n";
        return;
    }

    advance();

    std::string string_literal = source.substr(start + 1, current - start - 2);
    addLiteral(TokenType::STRING, std::any(string_literal));
    return;
}

void Scanner::scanNumber() {
    while (isdigit(peek())) {
        advance();
    }
    // Handle decimal numbers
    if (peek() == '.' && isdigit(peek())) {
        advance();
        while (isdigit(peek())) {
            advance();
        }
    }
    std::string number_literal = source.substr(start, current - start);
    int value = std::stoi(number_literal);
    addLiteral(TokenType::NUMBER, std::any(value));
}

char Scanner::peek() const {
    return source[current];
}






