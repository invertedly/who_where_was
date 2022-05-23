#pragma once

#include <string>
#include <utility>

#include "coord.h"

class Area final
{
	using range = std::pair<double, double>;

	range lat_range_;
	range lon_range_;

	std::string name_;
public:
	Area(const Coord c1, const Coord c2,
		const std::string& name = "");

	bool check_is_inside(const Coord& c) const;
	std::string get_name() const;

	void set_name(const std::string& name);
};

