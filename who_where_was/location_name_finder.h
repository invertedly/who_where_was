#pragma once
#include <optional>
#include <string>
#include <vector>

#include "area.h"
#include "KDTree.h"
#include "point.h"

class location_name_finder final
{
	std::vector<area> areas_;
	KDTree area_search_2d_tree_;
	double max_area_dist_;
public:
	location_name_finder(const std::vector<area>& areas);

	std::optional<std::string> find_name(const point& point) const;
};

