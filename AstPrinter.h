
#ifndef ASTPRINTER_H
#define ASTPRINTER_H

#include <any>
#include <string>
#include <vector>
#include "Expr.h"
#include "Stmt.h"


struct AstPrinter : public ExprVisitor, public StmtVisitor {
    std::any visitBinaryExpr(const Binary& expr) override;
    std::any visitGroupingExpr(const Grouping& expr) override;
    std::any visitLiteralExpr(const Literal& expr) override;
    std::any visitUnaryExpr(const Unary& expr) override;
    std::any visitVariableExpr(const Variable &expr) override;

    // Statement visitors
    std::any visitExpressionStmt(const ExpressionStmt& stmt) override;
    std::any visitPrintStmt(const PrintStmt& stmt) override;
    std::any visitVarStmt(const VarStmt &stmt) override;
    std::string parenthesize(const std::string& name, const std::vector<const Expr*>& expressions);
};
#endif //ASTPRINTER_H
