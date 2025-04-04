#ifndef INTERPRETER_H
#define INTERPRETER_H
#include <any>
#include "Expr.h"
#include "Stmt.h"

class Interpreter : public ExprVisitor, public StmtVisitor {
public:
    std::any visitBinaryExpr(const Binary& expr) override;
    std::any visitGroupingExpr(const Grouping& expr) override;
    std::any visitLiteralExpr(const Literal& expr) override;
    std::any visitUnaryExpr(const Unary& expr) override;
    std::any visitPrintStmt(const PrintStmt& stmt) override;
    std::any visitExpressionStmt(const ExpressionStmt& stmt) override;

    void interpret(const std::vector<std::unique_ptr<Stmt>>& statements);
};

#endif //INTERPRETER_H
