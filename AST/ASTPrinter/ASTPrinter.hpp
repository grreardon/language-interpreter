#pragma once

#include "../Expr/Expr.hpp"
#include "../Stmt/Statement.hpp"

class ASTPrinter
{
public:
    void print(const Expr *expr, int depth = 0) const;
    void print(const Stmt *stmt, int depth = 0) const;

private:
    void indent(int depth) const;
};
