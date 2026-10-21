#include <Expr.h>
#include <memory>

LiteralExpr::LiteralExpr(double value) : value(value) {};
BinaryExpr::BinaryExpr(std::unique_ptr<Expr> left, int op, std::unique_ptr<Expr> right) : left(std::move(left)), op(op), right(std::move(right)) {};
UnaryExpr::UnaryExpr(std::unique_ptr<Expr> expr, int op) : expr(std::move(expr)), op(op) {};
