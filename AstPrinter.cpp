#include "AstPrinter.h"
#include <iostream>

std::any AstPrinter::visitBinaryExpr(const Binary& expr) {
    return parenthesize(expr.op.lexeme, {expr.left.get(), expr.right.get()});
}

std::any AstPrinter::visitGroupingExpr(const Grouping& expr) {
    return parenthesize("group", {expr.expression.get()});
}

std::any AstPrinter::visitLiteralExpr(const Literal& expr) {
    if (!expr.value.has_value()) return std::string("nil");

    if (expr.value.type() == typeid(double)) {
        return std::to_string(std::any_cast<double>(expr.value));
    }

    if (expr.value.type() == typeid(int)) {
        return std::to_string(std::any_cast<int>(expr.value));
    }

    if (expr.value.type() == typeid(bool)) {
        return std::any_cast<bool>(expr.value) ? std::string("true") : std::string("false");
    }

    if (expr.value.type() == typeid(std::string)) {
        return std::any_cast<std::string>(expr.value);
    }
    return std::string("Unknown");
}

std::any AstPrinter::visitUnaryExpr(const Unary& expr) {
    return parenthesize(expr.op.lexeme, {expr.right.get()});
}

std::string AstPrinter::parenthesize(const std::string& name, const std::vector<const Expr*>& expressions) {
    std::string result = "(" + name;
    for (const Expr* expr : expressions) {
        std::any value = expr->accept(*this);

        if (value.type() == typeid(std::string)) {
            result += " " + std::any_cast<std::string>(value);
        } else if (value.type() == typeid(double)) {
            result += " " + std::to_string(std::any_cast<double>(value));
        } else if (value.type() == typeid(int)) {
            result += " " + std::to_string(std::any_cast<int>(value));
        } else if (value.type() == typeid(bool)) {
            result += std::any_cast<bool>(value) ? " true" : " false";
        } else {
            result += " [error: unexpected type]";
        }
    }
    result += ")";
    return result;
}