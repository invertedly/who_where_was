#pragma once
#include <stdexcept>
#include <string>

class Invalid_ts_format final : std::invalid_argument
{
public:
    explicit Invalid_ts_format(const std::string& message) : invalid_argument(message) { }
};
