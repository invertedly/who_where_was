#include "time.h"

#include <iomanip>
#include <sstream>

#include "exception.h"

namespace
{
	const char* input_format = "%Y-%m-%dT%H:%M:%S";

	time_t get_timet_from_ts(const std::string& ts)
	{
		std::istringstream in(ts);

		std::tm time{};

		if (in >> std::get_time(&time, input_format) && in.fail())
		{
			throw Invalid_ts_format("timestamp must have format: yyyy-mm-ddThh:mm:ss");
		}

		return std::mktime(&time);
	}
} 

Time::Time(const std::string& ts) : ts_(ts), time_id_(get_timet_from_ts(ts))
{
}

time_t Time::get_id() const
{
	return time_id_;
}

std::string Time::get_ts() const
{
	return ts_;
}

bool Time::operator<(const Time& rhs) const 
{
	return time_id_ < rhs.get_id();
}

bool Time::operator==(const Time& rhs) const 
{
	return time_id_ == rhs.time_id_;
}

