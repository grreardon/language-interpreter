
#include "Value.hpp"
#include "../../parser.tab.h"
#include "../../Runtime/Helpers/CheckTruthy.hpp"
#include <cmath>
#include <limits>
#include <stdexcept>
#include <type_traits>

bool above_limits(double l, double r)
{
    return (l < std::numeric_limits<int>::min() ||
            l > std::numeric_limits<int>::max() ||
            r < std::numeric_limits<int>::min() ||
            r > std::numeric_limits<int>::max());
};

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
            return *l - *r;
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
            return *l * *r;
        }
    }

    throw std::runtime_error("Invalid types for multiply");
}

Value divide(const Value &left, const Value &right)
{
    if (auto l = std::get_if<double>(&left))
    {
        if (auto r = std::get_if<double>(&right))
        {
            if (*r == 0)
                throw std::runtime_error("Division by zero");

            return *l / *r;
        }
    }

    throw std::runtime_error("Invalid types for division");
}

Value logical_or(const Value &left, const Value &right)
{
    bool left_val = checkTruthy(left);
    bool right_val = checkTruthy(right);

    return left_val || right_val;
}

Value logical_and(const Value &left, const Value &right)
{
    bool left_val = checkTruthy(left);
    bool right_val = checkTruthy(right);

    return left_val && right_val;
}

Value cmp(const Value &left, const Value &right, int op)
{
    switch (op)
    {
    case EQ:
        return left == right;
    case NEQ:
        return left != right;
    default:
        return std::visit([op](const auto &l, const auto &r) -> bool
                          {
            using L = std::decay_t<decltype(l)>;
            using R = std::decay_t<decltype(r)>;

            if constexpr (
                std::is_same_v<L, R> &&
                (std::is_same_v<L, double> ||
                 std::is_same_v<L, std::string> ||
                 std::is_same_v<L, char>))
            {
                switch (op)
                {
                case LEQ:
                    return l <= r;
                case GEQ:
                    return l >= r;
                case '>':
                    return l > r;
                case '<':
                    return l < r;
                }
                throw std::runtime_error("Invalid opcode");
            }
            else
            {
                throw std::runtime_error("Incompatible comparator types");
            } }, left, right);
    }
}

Value bit_or(const Value &left, const Value &right)
{
    if (auto l = std::get_if<double>(&left))
    {
        if (auto r = std::get_if<double>(&right))
        {
            if (std::isfinite(*l) && std::isfinite(*r) &&
                std::trunc(*l) == *l && std::trunc(*r) == *r)
            {
                if (above_limits(*l, *r))
                    throw std::runtime_error("Integer out of range");

                return static_cast<double>(
                    static_cast<int>(*l) | static_cast<int>(*r));
            }
            throw std::runtime_error("Bitwise operations require whole numbers");
        }
    }

    throw std::runtime_error("Invalid types for bit_or");
}

Value bit_xor(const Value &left, const Value &right)
{
    if (auto l = std::get_if<double>(&left))
    {
        if (auto r = std::get_if<double>(&right))
        {
            if (std::isfinite(*l) && std::isfinite(*r) &&
                std::trunc(*l) == *l && std::trunc(*r) == *r)
            {
                if (above_limits(*l, *r))
                    throw std::runtime_error("Integer out of range");

                return static_cast<double>(
                    static_cast<int>(*l) ^ static_cast<int>(*r));
            }
            throw std::runtime_error("Bitwise operations require whole numbers");
        }
    }

    throw std::runtime_error("Invalid types for bit_xor");
}

Value bit_and(const Value &left, const Value &right)
{
    if (auto l = std::get_if<double>(&left))
    {
        if (auto r = std::get_if<double>(&right))
        {
            if (std::isfinite(*l) && std::isfinite(*r) &&
                std::trunc(*l) == *l && std::trunc(*r) == *r)
            {
                if (above_limits(*l, *r))
                    throw std::runtime_error("Integer out of range");

                return static_cast<double>(
                    static_cast<int>(*l) & static_cast<int>(*r));
            }
            throw std::runtime_error("Bitwise operations require whole numbers");
        }
    }

    throw std::runtime_error("Invalid types for bit_and");
}

Value shift(const Value &left, const Value &right, int op)
{
    if (auto l = std::get_if<double>(&left))
    {
        if (auto r = std::get_if<double>(&right))
        {
            if (std::isfinite(*l) && std::isfinite(*r) &&
                std::trunc(*l) == *l && std::trunc(*r) == *r)
            {
                if (*l < std::numeric_limits<int>::min() ||
                    *l > std::numeric_limits<int>::max() ||
                    *r < 0 ||
                    *r >= std::numeric_limits<unsigned int>::digits)
                    throw std::runtime_error("Invalid shift range");

                int amount = static_cast<int>(*r);
                int number = static_cast<int>(*l);

                if (op == SL)
                {
                    if (number < 0 ||
                        number > (std::numeric_limits<int>::max() >> amount))
                        throw std::runtime_error("Invalid left shift");

                    return static_cast<double>(number << amount);
                }
                else if (op == SR)
                {
                    return static_cast<double>(number >> amount);
                }
                else
                {
                    throw std::runtime_error("Invalid operand");
                }
            }
            throw std::runtime_error("Bitwise operations require whole numbers");
        }
    }

    throw std::runtime_error("Invalid types for shift");
}

Value power(const Value &left, const Value &right)
{
    if (auto l = std::get_if<double>(&left))
    {
        if (auto r = std::get_if<double>(&right))
        {
            return std::pow(*l, *r);
        }
    }

    throw std::runtime_error("Pow only possible on numbers");
}

Value modulo(const Value &left, const Value &right)
{
    if (auto l = std::get_if<double>(&left))
    {
        if (auto r = std::get_if<double>(&right))
        {
            if (*r == 0)
                throw std::runtime_error("Modulo by zero");

            return std::fmod(*l, *r);
        }
    }

    throw std::runtime_error("Invalid types for modulo");
}
