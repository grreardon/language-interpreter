#pragma once

#include <string>
#include <memory>
#include <vector>
#include <variant>

class ExprVisitor
{
public:
    virtual void visitLiteralExpr(const LiteralExpr *) = 0;
    virtual void visitBinaryExpr(const BinaryExpr *) = 0;
    virtual void visitUnaryExpr(const UnaryExpr *) = 0;
    virtual void visitVariableExpr(const VariableExpr *) = 0;
    virtual void visitCallExpr(const CallExpr *) = 0;
    virtual void visitArrayExpr(const ArrayExpr *) = 0;
    virtual void visitIndexExpr(const IndexExpr *) = 0;
    virtual void visitMemberExpr(const MemberExpr *) = 0;
};
class Expr
{
public:
    virtual ~Expr() = default;
    virtual void accept(ExprVisitor &visitor) const = 0;
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
    void accept(ExprVisitor &visitor) const override
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

    void accept(ExprVisitor &visitor) const override
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
    void accept(ExprVisitor &visitor) const override
    {
        return visitor.visitUnaryExpr(this);
    }
};

class VariableExpr : public Expr
{
public:
    std::string name;
    explicit VariableExpr(std::string);
    void accept(ExprVisitor &visitor) const override
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
    void accept(ExprVisitor &visitor) const override
    {
        return visitor.visitCallExpr(this);
    }
};

class ArrayExpr : public Expr
{
public:
    std::vector<std::unique_ptr<Expr>> elements;
    explicit ArrayExpr(std::vector<std::unique_ptr<Expr>>);
    void accept(ExprVisitor &visitor) const override
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
    void accept(ExprVisitor &visitor) const override
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
    void accept(ExprVisitor &visitor) const override
    {
        return visitor.visitMemberExpr(this);
    }
};
