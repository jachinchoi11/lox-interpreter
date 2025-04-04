#include "Interpreter.h"
#include <iostream>

void Interpreter::interpret(const std::vector<std::unique_ptr<Stmt>>& statements) {
    for (const auto& stmt : statements) {
        stmt->accept(*this);
    }
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
    return 0;
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
        }
        if (expr.op.type == TokenType::GREATER) return leftVal > rightVal;
        if (expr.op.type == TokenType::LESS) return leftVal < rightVal;
        if (expr.op.type == TokenType::EQUAL) return leftVal == rightVal;
        if (expr.op.type == TokenType::GREATER_EQUAL) return leftVal >= rightVal;
        if (expr.op.type == TokenType::LESS_EQUAL) return leftVal <= rightVal;

    }

    if (left.type() == typeid(int) && right.type() == typeid(int)) {
        int leftVal = std::any_cast<int>(left);
        int rightVal = std::any_cast<int>(right);

        if (expr.op.type == TokenType::PLUS) return leftVal + rightVal;
        if (expr.op.type == TokenType::MINUS) return leftVal - rightVal;
        if (expr.op.type == TokenType::STAR) return leftVal * rightVal;
        if (expr.op.type == TokenType::SLASH) {
            if (rightVal == 0) throw std::runtime_error("Division by zero.");
        }
        if (expr.op.type == TokenType::EQUAL) return leftVal == rightVal;
        if (expr.op.type == TokenType::GREATER_EQUAL) return leftVal >= rightVal;
        if (expr.op.type == TokenType::LESS_EQUAL) return leftVal <= rightVal;
    }
    return 0;
}

std::any Interpreter::visitVariableExpr(const Variable &expr) {
    std::string key = expr.name.lexeme;
    std::any value = environment.get(key);
    if (value.type() == typeid(int)) {
        return std::any_cast<int>(value);
    }
    if (value.type() == typeid(bool)) {
        return std::any_cast<bool>(value);
    }
    if (value.type() == typeid(double)) {
        return std::any_cast<double>(value);
    }
    if (value.type() == typeid(std::string)) {
        return std::any_cast<std::string>(value);
    }
    throw std::runtime_error("Invalid variable type");
}


std::any Interpreter::visitPrintStmt(const PrintStmt& stmt) {
    // extract the value from the expression
    std::any value = stmt.expression->accept(*this);
    // Check if the value is of type string
    if (value.type() == typeid(std::string)) {
        // print the string value
        std::cout << std::any_cast<std::string>(value) << std::endl;
    } else if (value.type() == typeid(bool)) {
        std::cout << std::any_cast<bool>(value) << std::endl;
    } else if (value.type() == typeid(int)) {
        std::cout << std::any_cast<int>(value) << std::endl;
    }
    else if (value.type() == typeid(double)) {
        std::cout << std::any_cast<double>(value) << std::endl;
    }
    else {
        throw std::runtime_error("Expected a string value for print statement.");
    }
    return value;  // return the value after printing it
}

std::any Interpreter::visitExpressionStmt(const ExpressionStmt& stmt) {
    return stmt.expression->accept(*this);
}

std::any Interpreter::visitVarStmt(const VarStmt& stmt) {
    std::any value;
    if (stmt.current_value != nullptr) {
        value = stmt.current_value->accept(*this);
    }
    // Directly store value without casting to std::string
    environment.define(stmt.var_name.lexeme, value);
    return value;
}