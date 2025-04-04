#pragma once
#include "Token.h"

struct Binary;
struct Grouping;
struct Literal;
struct Unary;
struct Variable;

struct ExprVisitor {
    virtual std::any visitBinaryExpr(const Binary& expr) = 0;
    virtual std::any visitGroupingExpr(const Grouping& expr) = 0;
    virtual std::any visitLiteralExpr(const Literal& expr) = 0;
    virtual std::any visitUnaryExpr(const Unary& expr) = 0;
    virtual std::any visitVariableExpr(const Variable& expr) = 0;
    virtual ~ExprVisitor() = default;
};

