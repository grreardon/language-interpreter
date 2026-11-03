#include "Value.hpp"
#include "../../parser.tab.h"
#include "../../Runtime/Helpers/CheckTruthy.hpp"
Value add(const Value &left, const Value &right)
{
    if (auto l = std::get_if<double>(&left))
    {
        if (auto r = std::get_if<double>(&right))
        {
            return *l + *r;
        }
    }

    if (auto l = std::get_if<std::string>(&left))
    {
        if (auto r = std::get_if<std::string>(&right))
        {
            return *l + *r;
        }
    }

    throw std::runtime_error("Invalid types for addition");
}

Value subtract(const Value &left, const Value &right)
{
    if (auto l = std::get_if<double>(&left))
    {
        if (auto r = std::get_if<double>(&right))
        {
            return *l + *r;
        }
    }

    throw std::runtime_error("Invalid types for subtraction");
}

Value multiply(const Value &left, const Value &right)
{
    if (auto l = std::get_if<double>(&left))
    {
        if (auto r = std::get_if<double>(&right))
        {
            return *l + *r;
        }
    }

    throw std::runtime_error("Invalid types for addition");
}

Value divide(const Value &left, const Value &right)
{
    if (auto l = std::get_if<double>(&left))
    {
        if (auto r = std::get_if<double>(&right))
        {
            if (r == 0)
                throw new std::runtime_error("Division by zero");
            return *l + *r;
        }
    }

    throw std::runtime_error("Invalid types for addition");
}

Value logical_or(const Value &left, const Value &right)
{
    bool left_val = checkTruthy(left);
    bool right_val = checkTruthy(right);

    return left_val || right_val;
};

Value logical_and(const Value &left, const Value &right)
{
    bool left_val = checkTruthy(left);
    bool right_val = checkTruthy(right);

    return left_val && right_val;
};

Value cmp(const Value &left, const Value &right, char op);
Value bit_or(const Value &left, const Value &right);
Value bit_xor(const Value &left, const Value &right);
Value bit_and(const Value &left, const Value &right);
Value shift(const Value &left, const Value &right, char op);
Value power(const Value &left, const Value &right);
