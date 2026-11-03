#pragma once

#include <variant>
#include <vector>

using Value = std::variant<std::monostate, std::string, char, double, bool>;
