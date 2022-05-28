#include "timestamp.h"

#include <iomanip>
#include <sstream>

#include "exception.h"

namespace
{
	const char* input_format = "%Y-%m-%dT%H:%M:%S";

	time_t get_timet_from_timestamp(const std::string& ts)
	{
		std::istringstream in(ts);

		std::tm time{};

		in >> std::get_time(&time, input_format);

		if (in.fail())
		{
			throw Invalid_ts_format("timestamp must have format: yyyy-mm-ddThh:mm:ss");
		}

		return std::mktime(&time);
	}
} 

timestamp::timestamp(const std::string& ts) : ts_(ts), time_id_(get_timet_from_timestamp(ts))
{
}

time_t timestamp::get_id() const
{
	return time_id_;
}

const std::string& timestamp::get_ts() const
{
	return ts_;
}

bool timestamp::operator<(const timestamp& rhs) const 
{
	return time_id_ < rhs.get_id();
}

bool timestamp::operator==(const timestamp& rhs) const 
{
	return time_id_ == rhs.time_id_;
}

