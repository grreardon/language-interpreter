#include "./Interpreter.hpp"

Value Interpreter::visitLiteralExpr(const LiteralExpr *expr)
{
    Value result = std::visit(
        [](const auto &x) -> Value
        {
            return x;
        },
        expr->value);
}
Value Interpreter::visitBinaryExpr(const BinaryExpr *expr)
{
    Value left = evaluate(expr->left.get());
    Value right = evaluate(expr->right.get());

    switch (expr->op)
    {
    case '+':
        auto l = std::get_if<double>(&left);
        auto r = std::get_if<double>(&right);

        if (l && r)
            return *l + *r;

        throw std::runtime_error("Invalid operands for +");
    }
};

// TODO: Need to implement all these for runtime
Value visitUnaryExpr(const UnaryExpr *);
Value visitVariableExpr(const VariableExpr *);
Value visitCallExpr(const CallExpr *);
Value visitArrayExpr(const ArrayExpr *);
Value visitIndexExpr(const IndexExpr *);
Value visitMemberExpr(const MemberExpr *);
void visitLetStmt(const LetStmt *);
void visitAssignmentStmt(const AssignmentStmt *);
void visitExprStmt(const ExprStmt *);
void visitBlockStmt(const BlockStmt *);
void visitIfStmt(const IfStmt *);
void visitWhileStmt(const WhileStmt *);
void visitForStmt(const ForStmt *);
void visitFunctionStmt(const FunctionStmt *);
void visitReturnStmt(const ReturnStmt *);
void visitBreakStmt(const BreakStmt *);
void visitContinueStmt(const ContinueStmt *);
