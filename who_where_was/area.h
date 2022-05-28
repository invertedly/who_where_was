#pragma once

#include <string>
#include <utility>

#include "point.h"
#include "exception.h"

class area final
{
	std::pair<double, double> lat_range_;
	std::pair<double, double> lon_range_;

	std::string name_;
public:
	area(const point point1, const point point2,
		const std::string& name = "");

	bool check_is_inside(const point& point) const;
	const std::string& get_name() const;

	std::pair<double, double> get_lat_range() const;
	std::pair<double, double> get_lon_range() const;

	void set_name(const std::string& name);
};
