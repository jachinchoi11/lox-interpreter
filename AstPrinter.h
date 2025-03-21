
#ifndef ASTPRINTER_H
#define ASTPRINTER_H

#include <any>
#include <string>
#include <vector>
#include "Expr.h"

struct AstPrinter : public ExprVisitor {
    std::any visitBinaryExpr(const Binary& expr) override;
    std::any visitGroupingExpr(const Grouping& expr) override;
    std::any visitLiteralExpr(const Literal& expr) override;
    std::any visitUnaryExpr(const Unary& expr) override;

    std::string parenthesize(const std::string& name, const std::vector<const Expr*>& expressions);
};
#endif //ASTPRINTER_H
