#include "Parser.h"
#include <stdexcept>
#include <iostream>

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens), current(0) {}

std::vector<std::unique_ptr<Stmt>> Parser::parse() {
    std::vector<std::unique_ptr<Stmt>> statements;
    while (!isAtEnd()) {
        std::cout << "Parsing token: " << peek().lexeme << " (" << static_cast<int>(peek().type) << ")" << std::endl;
        statements.push_back(declaration()); // declaration takes precedence
    }
    return statements;
}

std::unique_ptr<Stmt> Parser::declaration() {
    if (match({VAR})) {
        return varDeclaration();
    }
    return statement();
}
std::unique_ptr<Stmt> Parser::statement() {
    // Parse print expresssions
    if (match({PRINT})) {
        return printStatement();
    }
    // Parse general expression statements
    return expressionStatement();
}

std::unique_ptr<Stmt> Parser::printStatement() {
    auto expr = expression();
    consume(SEMICOLON, "semicolon not there");
    return std::make_unique<PrintStmt>(std::move(expr));
}

std::unique_ptr<Stmt> Parser::expressionStatement() {
    auto expr = expression();
    consume(SEMICOLON, "semicolon not there");
    return std::make_unique<ExpressionStmt>(std::move(expr));
}

std::unique_ptr<Stmt> Parser::varDeclaration() {
    Token var_name = consume(IDENTIFIER, "identifier not there");
    consume(EQUAL, "equal not there ");
    auto expr = expression();
    consume(SEMICOLON, "semicolon not there");
    return std::make_unique<VarStmt>(var_name, std::move(expr));

}

std::unique_ptr<Expr> Parser::expression() {
    return equality();
}

std::unique_ptr<Expr> Parser::equality() {
    std::unique_ptr<Expr> expr = comparison();
    while (match({TokenType::EQUAL_EQUAL, TokenType::BANG_EQUAL})) {
        Token op = previous();
        std::unique_ptr<Expr> right = comparison();
        expr = std::make_unique<Binary>(std::move(expr), op, std::move(right));
    }
    return expr;
}

std::unique_ptr<Expr> Parser::comparison() {
    std::unique_ptr<Expr> expr = term();

    while (match({TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL})) {
        Token op = previous();
        std::unique_ptr<Expr> right = term();
        expr = std::make_unique<Binary>(std::move(expr), op, std::move(right));
    }

    return expr;
}

std::unique_ptr<Expr> Parser::term() {
    std::unique_ptr<Expr> expr = factor();
    while (match({TokenType::PLUS, TokenType::MINUS})) {
        Token op = previous();
        std::unique_ptr<Expr> right = factor();
        expr = std::make_unique<Binary>(std::move(expr), op, std::move(right));
    }
    return expr;
}

std::unique_ptr<Expr> Parser::factor() {
    std::unique_ptr<Expr> expr = unary();
    while (match({TokenType::STAR, TokenType::SLASH})) {
        Token op = previous();
        std::unique_ptr<Expr> right = unary();
        expr = std::make_unique<Binary>(std::move(expr), op, std::move(right));
    }
    return expr;
}

std::unique_ptr<Expr> Parser::unary() {
    if (match({TokenType::BANG, TokenType::MINUS})) {
        Token op = previous();
        std::unique_ptr<Expr> right = unary();
        return std::make_unique<Unary>(op, std::move(right));
    }
    return primary();
}

std::unique_ptr<Expr> Parser::primary() {
    // has highest priority
    if (match({TokenType::FALSE})) return std::make_unique<Literal>(false);
    if (match({TokenType::TRUE})) return std::make_unique<Literal>(true);
    if (match({TokenType::NUMBER})) {
        return std::make_unique<Literal>(previous().literal);
    }
    if (match({TokenType::STRING})) {
        return std::make_unique<Literal>(previous().literal);
    }
    if (match({TokenType::IDENTIFIER})) {
        return std::make_unique<Variable>(previous());
    }
    if (match({TokenType::LEFT_PAREN})) {
        std::unique_ptr<Expr> expr = expression();
        if (!match({TokenType::RIGHT_PAREN})) {
            throw std::runtime_error("Expected ')' after expression.");
        }
        return std::make_unique<Grouping>(std::move(expr));
    }
    return nullptr;
}

bool Parser::match(const std::vector<TokenType>& types) {
    for (TokenType type : types) {
        if (check(type)) {
            advance();
            return true;
        }
    }
    return false;
}

bool Parser::check(TokenType type) {
    if (isAtEnd()) {
        return false;
    }
    return peek().type == type;
}

Token Parser::advance() {
    if (!isAtEnd()) {
        current += 1;
    }
    return previous();
}

bool Parser::isAtEnd() {
    return peek().type == TokenType::END_OF;
}

Token Parser::peek() {
    return tokens[current];
}

Token Parser::previous() {
    return tokens[current - 1];
}

Token Parser::consume(TokenType type, std::string error) {
    if (check(type)) {
        return advance();
    } else {
        throw std::runtime_error(error);
    }
}