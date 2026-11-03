#pragma once

#include <string>
#include <memory>
#include <vector>
#include <variant>
#include "../Value/Value.hpp"
class LiteralExpr;
class BinaryExpr;
class UnaryExpr;
class VariableExpr;
class CallExpr;
class ArrayExpr;
class IndexExpr;
class MemberExpr;
class ExprVisitor
{
public:
    virtual Value visitLiteralExpr(const LiteralExpr *) = 0;
    virtual Value visitBinaryExpr(const BinaryExpr *) = 0;
    virtual Value visitUnaryExpr(const UnaryExpr *) = 0;
    virtual Value visitVariableExpr(const VariableExpr *) = 0;
    virtual Value visitCallExpr(const CallExpr *) = 0;
    virtual Value visitArrayExpr(const ArrayExpr *) = 0;
    virtual Value visitIndexExpr(const IndexExpr *) = 0;
    virtual Value visitMemberExpr(const MemberExpr *) = 0;
};
class Expr
{
public:
    virtual ~Expr() = default;
    virtual Value accept(ExprVisitor &visitor) const = 0;
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
    Value accept(ExprVisitor &visitor) const override
    {
        return visitor.visitLiteralExpr(this);
    }
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

    Value accept(ExprVisitor &visitor) const override
    {
        return visitor.visitBinaryExpr(this);
    }
};

class UnaryExpr : public Expr
{
public:
    std::unique_ptr<Expr> expr;
    int op;
    UnaryExpr(
        std::unique_ptr<Expr>,
        int);
    Value accept(ExprVisitor &visitor) const override
    {
        return visitor.visitUnaryExpr(this);
    }
};

class VariableExpr : public Expr
{
public:
    std::string name;
    explicit VariableExpr(std::string);
    Value accept(ExprVisitor &visitor) const override
    {
        return visitor.visitVariableExpr(this);
    }
};

class CallExpr : public Expr
{
public:
    std::unique_ptr<Expr> callee;
    std::vector<std::unique_ptr<Expr>> arguments;
    CallExpr(
        std::unique_ptr<Expr>,
        std::vector<std::unique_ptr<Expr>>);
    Value accept(ExprVisitor &visitor) const override
    {
        return visitor.visitCallExpr(this);
    }
};

class ArrayExpr : public Expr
{
public:
    std::vector<std::unique_ptr<Expr>> elements;
    explicit ArrayExpr(std::vector<std::unique_ptr<Expr>>);
    Value accept(ExprVisitor &visitor) const override
    {
        return visitor.visitArrayExpr(this);
    }
};

class IndexExpr : public Expr
{
public:
    std::unique_ptr<Expr> object;
    std::unique_ptr<Expr> index;
    IndexExpr(
        std::unique_ptr<Expr>,
        std::unique_ptr<Expr>);
    Value accept(ExprVisitor &visitor) const override
    {
        return visitor.visitIndexExpr(this);
    }
};

class MemberExpr : public Expr
{
public:
    std::unique_ptr<Expr> object;
    std::string member;
    MemberExpr(
        std::unique_ptr<Expr>,
        std::string);
    Value accept(ExprVisitor &visitor) const override
    {
        return visitor.visitMemberExpr(this);
    }
};
