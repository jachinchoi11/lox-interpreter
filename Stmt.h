#pragma once

#include <memory>
#include <vector>
#include "Expr.h"
#include "Token.h"
#include "StmtVisitor.h"

struct Stmt {
    virtual std::any accept(StmtVisitor& visitor) const = 0;
    virtual ~Stmt() = default;
};

struct ExpressionStmt : public Stmt {
    ExpressionStmt(std::unique_ptr<Expr> expression);
    std::any accept(StmtVisitor& visitor) const override;
    const std::unique_ptr<Expr> expression;
};

struct PrintStmt : public Stmt {
    PrintStmt(std::unique_ptr<Expr> expression);
    std::any accept(StmtVisitor& visitor) const override;
    const std::unique_ptr<Expr> expression;
};

struct VarStmt: public Stmt {
    VarStmt(Token varName, std::unique_ptr<Expr> current_value);
    std::any accept(StmtVisitor& visitor) const override;
    Token var_name;
    std::unique_ptr<Expr> current_value;
};
