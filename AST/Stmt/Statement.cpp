#include "Statement.hpp"
#include <utility>

LetStmt::LetStmt(std::string identifier, std::unique_ptr<Expr> value) : identifier(std::move(identifier)), value(std::move(value)) {};
AssignmentStmt::AssignmentStmt(std::unique_ptr<Expr> target, int op, std::unique_ptr<Expr> value) : target(std::move(target)), op(op), value(std::move(value)) {};
ExprStmt::ExprStmt(std::unique_ptr<Expr> expression) : expression(std::move(expression)) {};
BlockStmt::BlockStmt(std::vector<std::unique_ptr<Stmt>> statements) : statements(std::move(statements)) {};
IfStmt::IfStmt(std::unique_ptr<Expr> condition, std::unique_ptr<BlockStmt> thenBranch, std::unique_ptr<Stmt> elseBranch) : condition(std::move(condition)), thenBranch(std::move(thenBranch)), elseBranch(std::move(elseBranch)) {};
WhileStmt::WhileStmt(std::unique_ptr<Expr> expr, std::unique_ptr<BlockStmt> body) : expr(std::move(expr)), body(std::move(body)) {};
ForStmt::ForStmt(std::unique_ptr<Stmt> init, std::unique_ptr<Expr> expr, std::unique_ptr<Stmt> update, std::unique_ptr<BlockStmt> body) : init(std::move(init)), expr(std::move(expr)), update(std::move(update)), body(std::move(body)) {};
FunctionStmt::FunctionStmt(std::string name, std::vector<std::string> params, std::unique_ptr<BlockStmt> body) : name(std::move(name)), params(std::move(params)), body(std::move(body)) {};
ReturnStmt::ReturnStmt(std::unique_ptr<Expr> return_value) : return_value(std::move(return_value)) {};
