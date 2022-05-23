#include "location_name_finder.h"

std::string Location_name_finder::find(const Coord& c, const std::vector<Area>& known_areas)
{
	for (const auto& area: known_areas)
	{
		if (area.check_is_inside(c))
		{
			return area.get_name();
		}
	}

	return {};
}
