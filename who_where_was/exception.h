#pragma once
#include <stdexcept>
#include <string>

class Invalid_ts_format final : std::invalid_argument
{
public:
    explicit Invalid_ts_format(const std::string& message) : invalid_argument(message) { }
};

class invalid_area final : public std::invalid_argument
{
public:
	explicit invalid_area(const std::string& message) : invalid_argument(message) { }
};
