#pragma once
#include <unordered_map>

#include "location.h"
#include "time.h"

class User_info final
{
	using unord_map = std::unordered_map<Time, Location, Time_hash>;
	using const_it = unord_map::const_iterator;
	using it = unord_map::iterator;

	unord_map location_logs_;
public:
	void insert_or_assign(const Time& t, const Location& l);
	void erase(const Time& t);

	it find(const Time& t);
	it begin();
	it end();

	const_it cfind(const Time& t) const;
	const_it cbegin() const;
	const_it cend() const;
};
