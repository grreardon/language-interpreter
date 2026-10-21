#pragma once

#include <string>
#include <memory>
#include <vector>
#include <variant>

class Expr
{
public:
    virtual ~Expr() = default;
};
using LiteralValue = std::variant<
    double,
    std::string,
    char,
    bool>;

class LiteralExpr : public Expr
{
public:
    LiteralValue value;
    explicit LiteralExpr(LiteralValue);
};

class BinaryExpr : public Expr
{
public:
    std::unique_ptr<Expr> left;
    std::unique_ptr<Expr> right;
    int op;
    BinaryExpr(
        std::unique_ptr<Expr>,
        int,
        std::unique_ptr<Expr>);
};

class UnaryExpr : public Expr
{
public:
    std::unique_ptr<Expr> expr;
    int op;
    UnaryExpr(
        std::unique_ptr<Expr>,
        int);
};

class VariableExpr : public Expr
{
public:
    std::string name;
    explicit VariableExpr(std::string);
};

class CallExpr : public Expr
{
public:
    std::unique_ptr<Expr> callee;
    std::vector<std::unique_ptr<Expr>> arguments;
    CallExpr(
        std::unique_ptr<Expr>,
        std::vector<std::unique_ptr<Expr>>);
};

class ArrayExpr : public Expr
{
public:
    std::vector<std::unique_ptr<Expr>> elements;
    explicit ArrayExpr(std::vector<std::unique_ptr<Expr>>);
};

class IndexExpr : public Expr
{
public:
    std::unique_ptr<Expr> object;
    std::unique_ptr<Expr> index;
    IndexExpr(
        std::unique_ptr<Expr>,
        std::unique_ptr<Expr>);
};

class MemberExpr : public Expr
{
public:
    std::unique_ptr<Expr> object;
    std::string member;
    MemberExpr(
        std::unique_ptr<Expr>,
        std::string);
};
