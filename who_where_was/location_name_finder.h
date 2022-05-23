#pragma once
#include <string>
#include <vector>

#include "area.h"
#include "coord.h"

class Location_name_finder final
{
public:
	static std::string find(const Coord& c, const std::vector<Area>& known_areas);
};
