#ifndef PARSER_H
#define PARSER_H


#include <vector>
#include <memory>
#include "Expr.h"
#include "Token.h"
#include "Stmt.h"
class Parser {
public:
    Parser(const std::vector<Token>& tokens);
    std::vector<std::unique_ptr<Stmt>> parse();
private:

    const std::vector<Token>& tokens;
    int current = 0;

    Token consume(TokenType type, std::string error);
    bool match(const std::vector<TokenType>& types);
    bool check(TokenType type);
    Token advance();
    bool isAtEnd();
    Token peek();
    Token previous();

    std::unique_ptr<Stmt> statement();
    std::unique_ptr<Stmt> expressionStatement();
    std::unique_ptr<Stmt> printStatement();
    std::unique_ptr <Expr> expression();
    std::unique_ptr<Expr> equality();
    std::unique_ptr<Expr> comparison();
    std::unique_ptr<Expr> term();
    std::unique_ptr<Expr> factor();
    std::unique_ptr<Expr> unary();
    std::unique_ptr<Expr> primary();
    std::unique_ptr<Stmt> varDeclaration();
    std::unique_ptr<Stmt> declaration();

};
#endif //PARSER_H
