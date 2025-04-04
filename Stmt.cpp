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

VarStmt::VarStmt(Token name, std::unique_ptr<Expr> initializer)
    : var_name(name), current_value(std::move(initializer)) {}

// accept method to handle the visitor pattern
std::any VarStmt::accept(StmtVisitor& visitor) const {
    return visitor.visitVarStmt(*this);  // Dispatch the call to the correct visit method in the visitor
}