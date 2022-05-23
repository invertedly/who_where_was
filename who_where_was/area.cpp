#include "area.h"

#include <algorithm>
#include <vector>

Area::Area(const Coord c1, const Coord c2, const std::string& name) : name_(name)
{
	std::vector<double> lat = { c1.get_lat(), c2.get_lat() };
	std::vector<double> lon = { c1.get_lon(), c2.get_lon() };
	std::sort(lat.begin(), lat.end());
	std::sort(lon.begin(), lon.end());
	lat_range_ = std::make_pair(lat[0], lat[1]);
	lon_range_ = std::make_pair(lon[0], lon[1]);
}

bool Area::check_is_inside(const Coord& c) const
{
	return lat_range_.first < c.get_lat() < lat_range_.second
		&& lon_range_.first < c.get_lon() < lon_range_.second;
}

std::string Area::get_name() const
{
	return name_;
}

void Area::set_name(const std::string& name)
{
	name_ = name;
}
