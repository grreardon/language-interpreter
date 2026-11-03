#pragma once
#include "../Expr/Expr.hpp"
class Stmt
{
public:
    virtual ~Stmt() = default;
};

class LetStmt : public Stmt
{
public:
    std::string identifier;
    std::unique_ptr<Expr> value;
    LetStmt(std::string,
            std::unique_ptr<Expr>);
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
};

class ExprStmt : public Stmt
{
public:
    std::unique_ptr<Expr> expression;
    explicit ExprStmt(std::unique_ptr<Expr>);
};

class BlockStmt : public Stmt
{
public:
    std::vector<std::unique_ptr<Stmt>> statements;
    explicit BlockStmt(std::vector<std::unique_ptr<Stmt>>);
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
};

class WhileStmt : public Stmt
{
public:
    std::unique_ptr<Expr> expr;
    std::unique_ptr<BlockStmt> body;
    WhileStmt(std::unique_ptr<Expr>,
              std::unique_ptr<BlockStmt>);
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
};

class ReturnStmt : public Stmt
{
public:
    std::unique_ptr<Expr> return_value;
    explicit ReturnStmt(std::unique_ptr<Expr>);
};

class BreakStmt : public Stmt
{
};
class ContinueStmt : public Stmt
{
};
