#pragma once

#include <any>
#include <memory>
#include <vector>
#include "Token.h"

struct Binary;
struct Unary;
struct Grouping;
struct Literal;

struct ExprVisitor {
    virtual std::any visitBinaryExpr(const Binary& expr) = 0;
    virtual std::any visitGroupingExpr(const Grouping& expr) = 0;
    virtual std::any visitLiteralExpr(const Literal& expr) = 0;
    virtual std::any visitUnaryExpr(const Unary& expr) = 0;
    virtual ~ExprVisitor() = default;
};

// have derived visitors for each function (interpret, resolve, analyze)

struct Expr {
    virtual std::any accept(ExprVisitor& visitor) const = 0;
    virtual ~Expr() = default;
};

struct Binary : public Expr {
    Binary(std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right);
    std::any accept(ExprVisitor& visitor) const override;

    const std::unique_ptr<Expr> left;
    const Token op;
    const std::unique_ptr<Expr> right;
};

struct Grouping : public Expr {
    Grouping(std::unique_ptr<Expr> expression);
    std::any accept(ExprVisitor& visitor) const override;

    const std::unique_ptr<Expr> expression;
};

struct Literal : public Expr {
    Literal(std::any value);
    std::any accept(ExprVisitor& visitor) const override;
    const std::any value;
};

struct Unary : public Expr {
    Unary(Token op, std::unique_ptr<Expr> right);
    std::any accept(ExprVisitor& visitor) const override;

    const Token op;
    const std::unique_ptr<Expr> right;
};
