#include "Stmt.h"
#include "StmtVisitor.h"


ExpressionStmt::ExpressionStmt(std::unique_ptr<Expr> expression)
    : expression(std::move(expression)) {}

std::any ExpressionStmt::accept(StmtVisitor& visitor) const {
    return visitor.visitExpressionStmt(*this); // Assuming the visitor pattern is implemented
}

PrintStmt::PrintStmt(std::unique_ptr<Expr> expression)
    : expression(std::move(expression)) {}

std::any PrintStmt::accept(StmtVisitor& visitor) const {
    return visitor.visitPrintStmt(*this); // Assuming the visitor pattern is implemented
}