#pragma once
#include <ctime>
#include <string>

class timestamp final
{
	std::string ts_;
	time_t time_id_;
public:
	timestamp(const std::string& ts);

	time_t get_id() const;
	const std::string& get_ts() const;

	bool operator< (const timestamp& rhs) const;
	bool operator== (const timestamp& rhs) const;
};