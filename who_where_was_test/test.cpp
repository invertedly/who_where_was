#include "pch.h"

#include "../who_where_was/database.h"
#include "../who_where_was/location_name_finder.h"

TEST(Db, Test) {
	std::string ts1 = "2022-05-09T21:32:01 ";
	std::string ts2 = "2022-05-09T21:32:02 ";
	std::string ts3 = "2022-05-09T21:32:03 ";
	std::string ts4 = "2022-05-09T21:32:04 ";

	std::string id1 = "1 ";
	std::string id2 = "2 ";
	std::string id3 = "3 ";

	std::string coord1 = "10 10 ";
	std::string coord2 = "20 20 ";
	std::string coord3 = "30 30 ";
	std::string coord_unknwn = "100 100 ";

	std::string place1 = "Park ";
	std::string place2 = "School ";
	std::string place3 = "Shop ";
	std::string place_unknwn = "Unknown ";

	std::string place1_range = "5 5 15 15 ";
	std::string place2_range = "21 21 19 19 ";
	std::string place3_range = "29 29 31 31 ";

	std::istringstream logs(ts1 + id1 + coord1 + "\n" + 
		ts2 + id1 + coord2 + "\n" +
		ts3 + id1 + coord1 + "\n" +
		ts1 + id2 + coord3 + "\n" +
		ts3 + id2 + coord3 + "\n" +
		ts1 + id3 + coord_unknwn);

	std::istringstream places(place1 + place1_range + "\n" +
		place2 + place2_range + "\n" +
		place3 + place3_range);

	Database db;

	std::string ts;
	size_t id;
	double lon, lat;

	while (logs >> ts >> id >> lon >> lat)
	{
		Time t(ts);
		Location l(Coord(lat, lon));
		db.insert_or_assign(id, t, l);
	}

	//for (auto& it = db.cbegin(); it != db.cend(); it = next(it))
	//{
	//	for (auto& u_it = it->second.cbegin(); u_it != it->second.cend(); u_it = next(u_it))
	//	{
	//		std::cout << it->first << " " << u_it->first.get_ts() << " " << u_it->second.get_coord().get_lat() << " " << u_it->second.get_coord().get_lon() << std::endl;
	//	}
	//}
}