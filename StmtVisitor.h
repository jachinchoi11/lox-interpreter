#pragma once

#include <any>


struct ExpressionStmt;
struct PrintStmt;
struct StmtVisitor {
    virtual std::any visitExpressionStmt(const ExpressionStmt& stmt) = 0;
    virtual std::any visitPrintStmt(const PrintStmt& stmt) = 0;

    virtual ~StmtVisitor() = default;
};
