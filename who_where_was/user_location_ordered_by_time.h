#pragma once
#include <map>

#include "location.h"
#include "timestamp.h"

class user_location_ordered_by_time final
{
	std::map<timestamp, location> loc_ordered_by_time_;
public:
	void insert_or_assign(const timestamp& time, const location& loc);
	void erase(const timestamp& time);

	std::map<timestamp, location>::iterator find(const timestamp& time);
	std::map<timestamp, location>::iterator begin();
	std::map<timestamp, location>::iterator end();

	std::map<timestamp, location>::const_iterator cfind(const timestamp& time) const;
	std::map<timestamp, location>::const_iterator cbegin() const;
	std::map<timestamp, location>::const_iterator cend() const;
};
