#include "area.h"

#include <algorithm>
#include <vector>

namespace
{
	bool equal_double(const double lhs, const double rhs, const double precision=10E-30)
	{
		return lhs - precision <= rhs && rhs <= lhs + precision;
	}
}

area::area(const point point1, const point point2, const std::string& name) : name_(name)
{
	std::vector<double> lat = { point1.get_lat(), point2.get_lat() };
	std::vector<double> lon = { point1.get_lon(), point2.get_lon() };
	std::sort(lat.begin(), lat.end());
	std::sort(lon.begin(), lon.end());

	if (equal_double(lat[0], lat[1]) && equal_double(lon[0], lon[1]))
	{
		throw invalid_area("area must be constructed from two different points");
	}

	lat_range_ = std::make_pair(lat[0], lat[1]);
	lon_range_ = std::make_pair(lon[0], lon[1]);
}

bool area::check_is_inside(const point& point) const
{
	return lat_range_.first <= point.get_lat() &&
			point.get_lat() <= lat_range_.second && 
			lon_range_.first <= point.get_lon() &&
			point.get_lon()<= lon_range_.second;
}

const std::string& area::get_name() const
{
	return name_;
}

std::pair<double, double> area::get_lat_range() const
{
	return lat_range_;
}

std::pair<double, double> area::get_lon_range() const
{
	return lon_range_;
}

void area::set_name(const std::string& name)
{
	name_ = name;
}
