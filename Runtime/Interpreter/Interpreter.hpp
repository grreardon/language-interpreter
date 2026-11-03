#pragma once

#include "../../AST/Expr/Expr.hpp"
#include "../../AST/Stmt/Statement.hpp"
#include "../../AST/Value/Value.hpp"

class Interpreter : public StmtVisitor, public ExprVisitor
{
public:
    Value evaluate(const Expr *expr)
    {
        return expr->accept(*this);
    }
    void execute(const Stmt *stmt)
    {
        stmt->accept(*this);
    }
    Value visitLiteralExpr(const LiteralExpr *) override;
    Value visitBinaryExpr(const BinaryExpr *) override;
    Value visitUnaryExpr(const UnaryExpr *) override;
    Value visitVariableExpr(const VariableExpr *) override;
    Value visitCallExpr(const CallExpr *) override;
    Value visitArrayExpr(const ArrayExpr *) override;
    Value visitIndexExpr(const IndexExpr *) override;
    Value visitMemberExpr(const MemberExpr *) override;
    void visitLetStmt(const LetStmt *) override;
    void visitAssignmentStmt(const AssignmentStmt *) override;
    void visitExprStmt(const ExprStmt *) override;
    void visitBlockStmt(const BlockStmt *) override;
    void visitIfStmt(const IfStmt *) override;
    void visitWhileStmt(const WhileStmt *) override;
    void visitForStmt(const ForStmt *) override;
    void visitFunctionStmt(const FunctionStmt *) override;
    void visitReturnStmt(const ReturnStmt *) override;
    void visitBreakStmt(const BreakStmt *) override;
    void visitContinueStmt(const ContinueStmt *) override;
};
