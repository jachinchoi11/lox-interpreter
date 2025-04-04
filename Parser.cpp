#include "Parser.h"
#include <stdexcept>
#include <iostream>

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens), current(0) {}

std::vector<std::unique_ptr<Stmt>> Parser::parse() {
    std::vector<std::unique_ptr<Stmt>> statements;
    // Loop to parse each statement.
    while (!isAtEnd()) {
        std::cout << "Parsing token: " << peek().lexeme << " (" << static_cast<int>(peek().type) << ")" << std::endl;
        statements.push_back(statement());
    }
    // return the vector of statements directly.
    return statements;
}

std::unique_ptr<Stmt> Parser::statement() {
    if (match({PRINT})) {
        return printStatement();
    }

    // Parse general expression statements
    return expressionStatement();
}

std::unique_ptr<Stmt> Parser::printStatement() {
    // Ensure the next token is an expression to print
    auto expr = expression();
    // Ensure the statement ends with a semicolon
    consume(SEMICOLON);
    return std::make_unique<PrintStmt>(std::move(expr));
}

std::unique_ptr<Stmt> Parser::expressionStatement() {
    auto expr = expression();
    consume(SEMICOLON);
    return std::make_unique<ExpressionStmt>(std::move(expr));
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
    if (match({TokenType::STRING})) {  // Handling for strings
        return std::make_unique<Literal>(previous().literal);  // Assuming `previous().literal` stores the string value
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

void Parser::consume(TokenType type) {
    if (check(type)) {
        advance();
        return;
    } else {
        std::cerr << "Expected: " << static_cast<int>(type) << ", but got: " << static_cast<int>(peek().type) << " (" << peek().lexeme << ")" << std::endl;
        throw std::runtime_error("content is not as expected");
    }
}