#ifndef PARSER_H
#define PARSER_H


#include <vector>
#include <memory>
#include "Expr.h"
#include "Token.h"

class Parser {
public:
    Parser(const std::vector<Token>& tokens);

    std::unique_ptr<Expr> parse();
private:

    const std::vector<Token>& tokens;
    int current = 0;

    bool match(const std::vector<TokenType>& types);
    bool check(TokenType type);
    Token advance();
    bool isAtEnd();
    Token peek();
    Token previous();

    std::unique_ptr<Expr> expression();
    std::unique_ptr<Expr> equality();
    std::unique_ptr<Expr> comparison();
    std::unique_ptr<Expr> term();
    std::unique_ptr<Expr> factor();
    std::unique_ptr<Expr> unary();
    std::unique_ptr<Expr> primary();
};
#endif //PARSER_H
