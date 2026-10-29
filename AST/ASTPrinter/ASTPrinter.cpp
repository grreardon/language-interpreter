#include "ASTPrinter.hpp"

#include <iostream>
#include <string>
#include <variant>

void ASTPrinter::indent(int depth) const
{
    std::cout << std::string(depth * 2, ' ');
}

void ASTPrinter::print(const Expr *expr, int depth) const
{
    indent(depth);

    if (!expr)
    {
        std::cout << "null\n";
        return;
    }

    if (auto node = dynamic_cast<const LiteralExpr *>(expr))
    {
        std::cout << "LiteralExpr: ";
        std::visit([](const auto &value)
                   { std::cout << value; }, node->value);
        std::cout << '\n';
    }
    else if (auto node = dynamic_cast<const VariableExpr *>(expr))
    {
        std::cout << "VariableExpr: " << node->name << '\n';
    }
    else if (auto node = dynamic_cast<const BinaryExpr *>(expr))
    {
        std::cout << "BinaryExpr (op=" << node->op << ")\n";
        print(node->left.get(), depth + 1);
        print(node->right.get(), depth + 1);
    }
    else if (auto node = dynamic_cast<const UnaryExpr *>(expr))
    {
        std::cout << "UnaryExpr (op=" << node->op << ")\n";
        print(node->expr.get(), depth + 1);
    }
    else if (auto node = dynamic_cast<const CallExpr *>(expr))
    {
        std::cout << "CallExpr\n";
        indent(depth + 1);
        std::cout << "Callee:\n";
        print(node->callee.get(), depth + 2);

        indent(depth + 1);
        std::cout << "Arguments:\n";
        for (const auto &arg : node->arguments)
            print(arg.get(), depth + 2);
    }
    else if (auto node = dynamic_cast<const ArrayExpr *>(expr))
    {
        std::cout << "ArrayExpr\n";
        for (const auto &element : node->elements)
            print(element.get(), depth + 1);
    }
    else if (auto node = dynamic_cast<const IndexExpr *>(expr))
    {
        std::cout << "IndexExpr\n";
        print(node->object.get(), depth + 1);
        print(node->index.get(), depth + 1);
    }
    else if (auto node = dynamic_cast<const MemberExpr *>(expr))
    {
        std::cout << "MemberExpr: " << node->member << '\n';
        print(node->object.get(), depth + 1);
    }
    else
    {
        std::cout << "Unknown Expr\n";
    }
}

void ASTPrinter::print(const Stmt *stmt, int depth) const
{
    indent(depth);

    if (!stmt)
    {
        std::cout << "null\n";
        return;
    }

    if (auto node = dynamic_cast<const BlockStmt *>(stmt))
    {
        std::cout << "BlockStmt\n";
        for (const auto &child : node->statements)
            print(child.get(), depth + 1);
    }
    else if (auto node = dynamic_cast<const LetStmt *>(stmt))
    {
        std::cout << "LetStmt: " << node->identifier << '\n';
        print(node->value.get(), depth + 1);
    }
    else if (auto node = dynamic_cast<const AssignmentStmt *>(stmt))
    {
        std::cout << "AssignmentStmt (op=" << node->op << ")\n";
        print(node->target.get(), depth + 1);
        print(node->value.get(), depth + 1);
    }
    else if (auto node = dynamic_cast<const ExprStmt *>(stmt))
    {
        std::cout << "ExprStmt\n";
        print(node->expression.get(), depth + 1);
    }
    else if (auto node = dynamic_cast<const IfStmt *>(stmt))
    {
        std::cout << "IfStmt\n";
        indent(depth + 1);
        std::cout << "Condition:\n";
        print(node->condition.get(), depth + 2);

        indent(depth + 1);
        std::cout << "Then:\n";
        print(node->thenBranch.get(), depth + 2);

        if (node->elseBranch)
        {
            indent(depth + 1);
            std::cout << "Else:\n";
            print(node->elseBranch.get(), depth + 2);
        }
    }
    else if (auto node = dynamic_cast<const WhileStmt *>(stmt))
    {
        std::cout << "WhileStmt\n";
        print(node->expr.get(), depth + 1);
        print(node->body.get(), depth + 1);
    }
    else if (auto node = dynamic_cast<const ForStmt *>(stmt))
    {
        std::cout << "ForStmt\n";

        indent(depth + 1);
        std::cout << "Init:\n";
        print(node->init.get(), depth + 2);

        indent(depth + 1);
        std::cout << "Condition:\n";
        print(node->expr.get(), depth + 2);

        indent(depth + 1);
        std::cout << "Update:\n";
        print(node->update.get(), depth + 2);

        indent(depth + 1);
        std::cout << "Body:\n";
        print(node->body.get(), depth + 2);
    }
    else if (auto node = dynamic_cast<const FunctionStmt *>(stmt))
    {
        std::cout << "FunctionStmt: " << node->name << '\n';

        indent(depth + 1);
        std::cout << "Parameters:";
        for (const auto &param : node->params)
            std::cout << ' ' << param;
        std::cout << '\n';

        print(node->body.get(), depth + 1);
    }
    else if (auto node = dynamic_cast<const ReturnStmt *>(stmt))
    {
        std::cout << "ReturnStmt\n";
        if (node->return_value)
            print(node->return_value.get(), depth + 1);
    }
    else if (dynamic_cast<const BreakStmt *>(stmt))
    {
        std::cout << "BreakStmt\n";
    }
    else if (dynamic_cast<const ContinueStmt *>(stmt))
    {
        std::cout << "ContinueStmt\n";
    }
    else
    {
        std::cout << "Unknown Stmt\n";
    }
}
