#pragma once
#include "../Expr/Expr.hpp"
class LetStmt;
class AssignmentStmt;
class ExprStmt;
class BlockStmt;
class IfStmt;
class WhileStmt;
class ForStmt;
class FunctionStmt;
class ReturnStmt;
class BreakStmt;
class ContinueStmt;

class StmtVisitor
{
public:
    virtual ~StmtVisitor() = default;
    virtual void visitLetStmt(const LetStmt *) = 0;
    virtual void visitAssignmentStmt(const AssignmentStmt *) = 0;
    virtual void visitExprStmt(const ExprStmt *) = 0;
    virtual void visitBlockStmt(const BlockStmt *) = 0;
    virtual void visitIfStmt(const IfStmt *) = 0;
    virtual void visitWhileStmt(const WhileStmt *) = 0;
    virtual void visitForStmt(const ForStmt *) = 0;
    virtual void visitFunctionStmt(const FunctionStmt *) = 0;
    virtual void visitReturnStmt(const ReturnStmt *) = 0;
    virtual void visitBreakStmt(const BreakStmt *) = 0;
    virtual void visitContinueStmt(const ContinueStmt *) = 0;
};
class Stmt
{
public:
    virtual ~Stmt() = default;
    virtual void accept(StmtVisitor &visitor) const = 0;
};

class LetStmt : public Stmt
{
public:
    std::string identifier;
    std::unique_ptr<Expr> value;
    LetStmt(std::string,
            std::unique_ptr<Expr>);
    void accept(StmtVisitor &visitor) const override
    {
        return visitor.visitLetStmt(this);
    }
};

class AssignmentStmt : public Stmt
{
public:
    std::unique_ptr<Expr> target;
    int op;
    std::unique_ptr<Expr> value;
    AssignmentStmt(std::unique_ptr<Expr>,
                   int,
                   std::unique_ptr<Expr>);
    void accept(StmtVisitor &visitor) const override
    {
        return visitor.visitAssignmentStmt(this);
    }
};

class ExprStmt : public Stmt
{
public:
    std::unique_ptr<Expr> expression;
    explicit ExprStmt(std::unique_ptr<Expr>);
    void accept(StmtVisitor &visitor) const override
    {
        return visitor.visitExprStmt(this);
    }
};

class BlockStmt : public Stmt
{
public:
    std::vector<std::unique_ptr<Stmt>> statements;
    explicit BlockStmt(std::vector<std::unique_ptr<Stmt>>);
    void accept(StmtVisitor &visitor) const override
    {
        return visitor.visitBlockStmt(this);
    }
};

class IfStmt : public Stmt
{
public:
    std::unique_ptr<Expr> condition;
    std::unique_ptr<BlockStmt> thenBranch;
    std::unique_ptr<Stmt> elseBranch;
    IfStmt(std::unique_ptr<Expr>,
           std::unique_ptr<BlockStmt>,
           std::unique_ptr<Stmt>);
    void accept(StmtVisitor &visitor) const override
    {
        return visitor.visitIfStmt(this);
    }
};

class WhileStmt : public Stmt
{
public:
    std::unique_ptr<Expr> expr;
    std::unique_ptr<BlockStmt> body;
    WhileStmt(std::unique_ptr<Expr>,
              std::unique_ptr<BlockStmt>);
    void accept(StmtVisitor &visitor) const override
    {
        return visitor.visitWhileStmt(this);
    }
};

class ForStmt : public Stmt
{
public:
    std::unique_ptr<Stmt> init;
    std::unique_ptr<Expr> expr;
    std::unique_ptr<Stmt> update;
    std::unique_ptr<BlockStmt> body;
    ForStmt(std::unique_ptr<Stmt>,
            std::unique_ptr<Expr>,
            std::unique_ptr<Stmt>,
            std::unique_ptr<BlockStmt>);
    void accept(StmtVisitor &visitor) const override
    {
        return visitor.visitForStmt(this);
    }
};

class FunctionStmt : public Stmt
{
public:
    std::string name;
    std::vector<std::string> params;
    std::unique_ptr<BlockStmt> body;
    FunctionStmt(std::string,
                 std::vector<std::string>,
                 std::unique_ptr<BlockStmt>);
    void accept(StmtVisitor &visitor) const override
    {
        return visitor.visitFunctionStmt(this);
    }
};

class ReturnStmt : public Stmt
{
public:
    std::unique_ptr<Expr> return_value;
    explicit ReturnStmt(std::unique_ptr<Expr>);
    void accept(StmtVisitor &visitor) const override
    {
        return visitor.visitReturnStmt(this);
    }
};

class BreakStmt : public Stmt
{
public:
    void accept(StmtVisitor &visitor) const override
    {
        return visitor.visitBreakStmt(this);
    }
};
class ContinueStmt : public Stmt
{
public:
    void accept(StmtVisitor &visitor) const override
    {
        return visitor.visitContinueStmt(this);
    }
};
