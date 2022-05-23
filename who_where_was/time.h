#pragma once
#include <ctime>
#include <string>

class Time final
{
	std::string ts_;
	time_t time_id_;
public:
	Time(const std::string& ts);

	time_t get_id() const;
	std::string get_ts() const;

	bool operator< (const Time& rhs) const;
	bool operator== (const Time& rhs) const;
};

class Time_hash final
{
public:
	time_t operator()(const Time& t) const { return t.get_id(); }
};