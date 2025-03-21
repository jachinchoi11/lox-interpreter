//
// Created by Jachin Choi on 2/28/25.
//
#include "Expr.h"


Binary::Binary(std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right)
    : left(std::move(left)), op(std::move(op)), right(std::move(right)) {}

std::any Binary::accept(ExprVisitor& visitor) const {
    return visitor.visitBinaryExpr(*this);
}

Grouping::Grouping(std::unique_ptr<Expr> expression)
    : expression(std::move(expression)) {}

std::any Grouping::accept(ExprVisitor& visitor) const {
    return visitor.visitGroupingExpr(*this);
}

Literal::Literal(std::any value) : value(std::move(value)) {}

std::any Literal::accept(ExprVisitor& visitor) const {
    return visitor.visitLiteralExpr(*this);
}

Unary::Unary(Token op, std::unique_ptr<Expr> right)
    : op(std::move(op)), right(std::move(right)) {}

std::any Unary::accept(ExprVisitor& visitor) const {
    return visitor.visitUnaryExpr(*this);
}
