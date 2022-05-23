#include "user_info.h"

void User_info::insert_or_assign(const Time& t, const Location& l)
{
	location_logs_.insert_or_assign(t, l);
}

void User_info::erase(const Time& t)
{
	location_logs_.erase(t);
}

User_info::it User_info::find(const Time& t)
{
	return location_logs_.find(t);
}

User_info::it User_info::begin()
{
	return location_logs_.begin();
}

User_info::it User_info::end()
{
	return location_logs_.end();
}

User_info::const_it User_info::cfind(const Time& t) const
{
	return location_logs_.find(t);
}

User_info::const_it User_info::cbegin() const
{
	return location_logs_.begin();
}

User_info::const_it User_info::cend() const
{
	return location_logs_.end();
}
