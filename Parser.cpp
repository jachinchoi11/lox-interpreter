#include "Parser.h"
#include <stdexcept>

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens) {}

std::unique_ptr<Expr> Parser::parse() {
    return expression();
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
    // has highest prioirty
    if (match({TokenType::FALSE})) return std::make_unique<Literal>(false);
    if (match({TokenType::TRUE})) return std::make_unique<Literal>(true);
    if (match({TokenType::NUMBER})) {
        return std::make_unique<Literal>(previous().literal);
    }

    if (match({TokenType::LEFT_PAREN})) {
        std::unique_ptr<Expr> expr = expression();
        if (!match({TokenType::RIGHT_PAREN})) {
            throw std::runtime_error("Expected ')' after expression.");
        }
        return std::make_unique<Grouping>(std::move(expr));
    }
    return 0;
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
        current+= 1;
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
