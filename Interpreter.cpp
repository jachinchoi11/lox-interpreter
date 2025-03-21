#include "Interpreter.h"
#include <iostream>

std::any Interpreter::interpret(const Expr& expression) {
    return expression.accept(*this);
}

std::any Interpreter::visitLiteralExpr(const Literal& expr) {
    return expr.value;
}
std::any Interpreter::visitGroupingExpr(const Grouping& expr) {
    return expr.expression->accept(*this);
}
std::any Interpreter::visitUnaryExpr(const Unary& expr) {
    std::any right = expr.right->accept(*this);

    if (expr.op.type == TokenType::MINUS) {
        if (right.type() == typeid(double)) {
            return -std::any_cast<double>(right);
        }
        if (right.type() == typeid(int)) {
            return -std::any_cast<int>(right);
        }
    }
    if (expr.op.type == TokenType::BANG) {
        if (right.type() == typeid(bool)) {
            return !std::any_cast<bool>(right);
        }
    }
}

std::any Interpreter::visitBinaryExpr(const Binary& expr) {
    // only have support for +, - , *, /
    // add suppport for ==, !=, >=, <= , > , <


    std::any left = expr.left->accept(*this);
    std::any right = expr.right->accept(*this);

    if (left.type() == typeid(double) && right.type() == typeid(double)) {
        // make sure type is right
        double leftVal = std::any_cast<double>(left);
        double rightVal = std::any_cast<double>(right);

        if (expr.op.type == TokenType::PLUS) return leftVal + rightVal;
        if (expr.op.type == TokenType::MINUS) return leftVal - rightVal;
        if (expr.op.type == TokenType::STAR) return leftVal * rightVal;
        if (expr.op.type == TokenType::SLASH) {
            if (rightVal == 0) throw std::runtime_error("Division by zero.");
            return leftVal / rightVal;
        }
    }

    if (left.type() == typeid(int) && right.type() == typeid(int)) {
        int leftVal = std::any_cast<int>(left);
        int rightVal = std::any_cast<int>(right);

        if (expr.op.type == TokenType::PLUS) return leftVal + rightVal;
        if (expr.op.type == TokenType::MINUS) return leftVal - rightVal;
        if (expr.op.type == TokenType::STAR) return leftVal * rightVal;
        if (expr.op.type == TokenType::SLASH) {
            if (rightVal == 0) throw std::runtime_error("Division by zero.");
            return static_cast<double>(leftVal) / rightVal;
        }
    }
}
