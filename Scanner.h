

#ifndef SCANNER_H
#define SCANNER_H
#include <string>
#include <vector>
#include "Token.h"
#include <map>

class Scanner {
    std::string source;
    unsigned int start{0};
    unsigned int current{0};
    unsigned int line{1};
    char current_char;
    static std::map<std::string, TokenType> possible_keywords;
    void scanIdentifier();
    void advance();
    bool isAtEnd();
    void scanToken();
    void addToken(TokenType type);
    void createToken(TokenType type);
    bool nextToken(char expected);
    std::vector<Token> tokens;
    void scanString();
    char peek() const;
    void scanNumber();
    void addLiteral(TokenType type, std::any value);

public:
    Scanner(const std::string& source);
    std::vector<Token> scanTokens();
};
#endif //SCANNER_H
