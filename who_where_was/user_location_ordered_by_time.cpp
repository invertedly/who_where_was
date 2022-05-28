#include "user_location_ordered_by_time.h"

void user_location_ordered_by_time::insert_or_assign(const timestamp& time, const location& loc)
{
	loc_ordered_by_time_.insert_or_assign(time, loc);
}

void user_location_ordered_by_time::erase(const timestamp& time)
{
	loc_ordered_by_time_.erase(time);
}

std::map<timestamp, location>::iterator user_location_ordered_by_time::find(
	const timestamp& time)
{
	return loc_ordered_by_time_.find(time);
}

std::map<timestamp, location>::iterator user_location_ordered_by_time::begin()
{
	return loc_ordered_by_time_.begin();
}

std::map<timestamp, location>::iterator user_location_ordered_by_time::end()
{
	return loc_ordered_by_time_.end();
}

std::map<timestamp, location>::const_iterator user_location_ordered_by_time::cfind(
	const timestamp& time) const
{
	return loc_ordered_by_time_.find(time);
}

std::map<timestamp, location>::const_iterator user_location_ordered_by_time::cbegin() const
{
	return loc_ordered_by_time_.begin();
}

std::map<timestamp, location>::const_iterator user_location_ordered_by_time::cend() const
{
	return loc_ordered_by_time_.end();
}
