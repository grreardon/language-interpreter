#pragma once

#include <memory>
class Expr
{
public:
    virtual ~Expr() = default;
};

class LiteralExpr : public Expr
{
public:
    double value;
    explicit LiteralExpr(double value);
};

class BinaryExpr : public Expr
{
public:
    std::unique_ptr<Expr> left;
    std::unique_ptr<Expr> right;
    int op;
    BinaryExpr(
        std::unique_ptr<Expr> left,
        int op,
        std::unique_ptr<Expr> right);
};

class UnaryExpr : public Expr
{
public:
    std::unique_ptr<Expr> expr;
    int op;
    UnaryExpr(
        std::unique_ptr<Expr> expr,
        int op);
};
