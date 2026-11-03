#include "./CheckTruthy.hpp"

// TODO: Need to do for arr after implemented
bool checkTruthy(Value &val)
{
    if (auto l = std::get_if<double>(&val))
    {
        return *l != 0;
    }

    if (auto l = std::get_if<std::string>(&val))
    {
        return l->length() > 0;
    }

    if (auto l = std::get_if<bool>(&val))
    {
        return *l;
    }

    if (auto l = std::get_if<std::monostate>(&val))
    {
        return false;
    }

    throw std::runtime_error("Invalid type for comparison");
}
