#ifndef INTERPRETER_H
#define INTERPRETER_H
#include <any>
#include "Expr.h"

class Interpreter : public ExprVisitor {
public:
    std::any visitBinaryExpr(const Binary& expr) override;
    std::any visitGroupingExpr(const Grouping& expr) override;
    std::any visitLiteralExpr(const Literal& expr) override;
    std::any visitUnaryExpr(const Unary& expr) override;

    std::any interpret(const Expr& expression);
};

#endif //INTERPRETER_H
