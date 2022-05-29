#include "location_name_finder.h"

#include <iostream>

namespace
{
	double get_area_dist(const area& area)
	{
		auto [x_min, x_max] = area.get_lat_range();
		auto [y_min, y_max] = area.get_lon_range();

		return sqrt(pow(x_max - x_min, 2) + pow(y_max - y_min, 2));
	}
}

location_name_finder::location_name_finder(const std::vector<area>& areas) :
	areas_(areas), max_area_dist_(0)
{
	std::vector<std::vector<double>> area_search_keys;

	area_search_keys.reserve(areas.size());

	for (const auto& area : areas)
	{
		area_search_keys.push_back({area.get_lat_range().first, area.get_lon_range().first});

		const double new_area_dist = get_area_dist(area);

		if (new_area_dist > max_area_dist_)
		{
			max_area_dist_ = new_area_dist;
		}
	}

	area_search_2d_tree_ = KDTree(area_search_keys);
}

std::vector<std::string> location_name_finder::find_names(const point& point) const
{
	std::vector<size_t> indices_to_check = area_search_2d_tree_.neighborhood_indices({ point.get_lat(), point.get_lon() }, max_area_dist_);

	std::vector<std::string> names;

	for (const auto i : indices_to_check)
	{
		if (areas_[i].check_is_inside(point))
		{
			names.push_back(areas_[i].get_name());
		}
	}

	std::sort(names.begin(), names.end());

	return names;
}

