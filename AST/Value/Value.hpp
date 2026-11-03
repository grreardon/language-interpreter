#pragma once

#include <variant>
#include <vector>
// TODO: have value for arr and func too
using Value = std::variant<std::monostate, std::string, char, double, bool>;
Value add(const Value &left, const Value &right);
Value subtract(const Value &left, const Value &right);
Value multiply(const Value &left, const Value &right);
Value divide(const Value &left, const Value &right);
Value logical_or(const Value &left, const Value &right);
Value logical_and(const Value &left, const Value &right);
Value cmp(const Value &left, const Value &right, char op);
Value bit_or(const Value &left, const Value &right);
Value bit_xor(const Value &left, const Value &right);
Value bit_and(const Value &left, const Value &right);
Value shift(const Value &left, const Value &right, char op);
Value power(const Value &left, const Value &right);
