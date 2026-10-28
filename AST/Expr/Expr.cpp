#include "Expr.hpp"
#include <memory>

LiteralExpr::LiteralExpr(LiteralValue value) : value(value) {};
BinaryExpr::BinaryExpr(std::unique_ptr<Expr> left, int op, std::unique_ptr<Expr> right) : left(std::move(left)), op(op), right(std::move(right)) {};
UnaryExpr::UnaryExpr(std::unique_ptr<Expr> expr, int op) : expr(std::move(expr)), op(op) {};
CallExpr::CallExpr(std::unique_ptr<Expr> callee, std::vector<std::unique_ptr<Expr>> arguments) : callee(std::move(callee)), arguments(std::move(arguments)) {};
ArrayExpr::ArrayExpr(std::vector<std::unique_ptr<Expr>> elements) : elements(std::move(elements)) {};
IndexExpr::IndexExpr(std::unique_ptr<Expr> object, std::unique_ptr<Expr> index) : object(std::move(object)), index(std::move(index)) {};
MemberExpr::MemberExpr(std::unique_ptr<Expr> object, std::string member) : object(std::move(object)), member(std::move(member)) {};
VariableExpr::VariableExpr(std::string name) : name(std::move(name)) {};
