#include "pch.h"

#include "../who_where_was/database.h"
#include "../who_where_was/location_name_finder.h"

namespace
{
	const std::string ts1 = "2000-01-01T00:00:01 ";
	const std::string ts2 = "2000-01-01T00:00:02 ";
	const std::string ts3 = "2000-01-01T00:00:03 ";
	const std::string ts_invalid = "00:00:04 2000-01-01 ";

	const std::string id1 = "1 ";
	const std::string id2 = "2 ";
	const std::string id3 = "3 ";
	const std::string id4 = "4 ";

	const std::string coord1 = "10 10 ";
	const std::string coord2 = "20 20 ";
	const std::string coord3 = "-30 -30 ";
	const std::string coord4 = "40 40 ";
	const std::string coord_unknwn = "0 0 ";

	const std::string place1 = "Place1 ";
	const std::string place2 = "Place2 ";
	const std::string place3 = "Place3 ";
	const std::string place4 = "Place4 ";
	const std::string place_unknwn = "Unknown ";

	const std::string place1_range = "9 9 11 11 ";
	const std::string place2_range = "20 20 21 21 ";
	const std::string place3_range = "-29 -29 -31 -31 ";
	const std::string place4_range = "40 40 40 40 ";

	const std::string logs_u1(
		ts1 + id1 + coord1 + "\n" +
		ts2 + id1 + coord2 + "\n" +
		ts3 + id1 + coord1 + "\n"
	);

	const std::string logs_u2(
		ts1 + id2 + coord3 + "\n" +
		ts2 + id2 + coord3 + "\n"
	);

	const std::string logs_u3(
		ts1 + id3 + coord1 + "\n" +
		ts2 + id3 + coord_unknwn + "\n"
	);

	const std::string logs_u4(
		ts1 + id4 + coord_unknwn + "\n"
	);

	const std::string logs_init_all(
		logs_u1 +
		logs_u2 +
		logs_u3 +
		logs_u4
	);

	const std::string places_init_all(
		place1 + place1_range + "\n" +
		place2 + place2_range + "\n" +
		place3 + place3_range
	);

	const std::string places_answer(
		place1 + "\n" +
		place1 + "\n" +
		place1 + "\n" +
		"unknown" + "\n"
	);

	std::optional<std::string> get_user_logs(const size_t id)
	{
		switch (id)
		{
		case 1: return { logs_u1 };
		case 2: return { logs_u2 };
		case 3: return { logs_u3 };
		case 4: return { logs_u4 };
		default: return std::nullopt;
		}
	}

	database init_db()
	{
		std::istringstream logs(logs_init_all);

		database db;

		std::string ts;
		size_t id;
		double lon, lat;

		while (logs >> ts >> id >> lon >> lat)
		{
			timestamp time(ts);
			location loc(point(lat, lon));
			db.insert_or_assign(id, time, loc);
		}

		return db;
	}
}

TEST(database, db_insert) {
	database db = init_db();

	size_t count = 0;

	for (auto& [user_id, user_data] : db)
	{
		count++;

		std::ostringstream out;

		for (auto& [time, location] : user_data)
		{
			out
			<< time.get_ts() << " "
			<< user_id.get_id() << " "
			<< location.get_coord().get_lat() << " "
			<< location.get_coord().get_lon() << " "
			<< std::endl;
		}

		ASSERT_EQ(out.str(), get_user_logs(user_id.get_id()).value_or("no logs for user " 
			+ std::stringstream(user_id.get_id()).str()));
	}

	ASSERT_EQ(count, 4);
}

TEST(database, db_erase) {
	database db = init_db();

	std::vector<size_t> user_ids;

	for (const auto& record : db)
	{
		user_ids.push_back(record.first.get_id());
	}

	std::vector<size_t> answer = { 1, 2, 3, 4 };
	std::sort(user_ids.begin(), user_ids.end());
	ASSERT_EQ(user_ids, answer);

	db.erase(4);
	user_ids.clear();

	for (const auto& record : db)
	{
		user_ids.push_back(record.first.get_id());
	}

	answer = { 1, 2, 3 };
	std::sort(user_ids.begin(), user_ids.end());
	ASSERT_EQ(user_ids, answer);
}

TEST(Area, check_is_inside_common)
{
	std::istringstream in_place1(place1 + place1_range);

	std::string name;
	double lat1 = 0, lon1 = 0, lat2 = 0, lon2 = 0;

	ASSERT_TRUE(in_place1 >> name >> lat1 >> lon1 >> lat2 >> lon2);
	area area1({ lat1, lon1 }, { lat2, lon2 }, name);
	ASSERT_TRUE(area1.check_is_inside({10, 10}));
	ASSERT_TRUE(!area1.check_is_inside({20, 20}));
	ASSERT_TRUE(!area1.check_is_inside({-30, -30}));
	ASSERT_TRUE(!area1.check_is_inside({0, 0}));
}

TEST(Area, check_is_inside_border)
{
	std::string name;
	double lat1 = 0, lon1 = 0, lat2 = 0, lon2 = 0;

	std::istringstream in_place2(place2 + place2_range);

	ASSERT_TRUE(in_place2 >> name >> lat1 >> lon1 >> lat2 >> lon2);
	area area2({ lat1, lon1 }, { lat2, lon2 }, name);
	ASSERT_TRUE(!area2.check_is_inside({ 10, 10 }));
	ASSERT_TRUE(area2.check_is_inside({ 20, 20 }));
	ASSERT_TRUE(!area2.check_is_inside({ -30, -30 }));
	ASSERT_TRUE(!area2.check_is_inside({ 0, 0 }));

	std::istringstream in_place3(place3 + place3_range);

	ASSERT_TRUE(in_place3 >> name >> lat1 >> lon1 >> lat2 >> lon2);
	area area3({ lat1, lon1 }, { lat2, lon2 }, name);
	ASSERT_TRUE(!area3.check_is_inside({ 10, 10 }));
	ASSERT_TRUE(!area3.check_is_inside({ 20, 20 }));
	ASSERT_TRUE(area3.check_is_inside({ -30, -30 }));
	ASSERT_TRUE(!area3.check_is_inside({ 0, 0 }));
}

TEST(Area, ctor_invalid_arg)
{
	EXPECT_THROW(area area({ 1, 1 }, { 1, 1 }), invalid_area);
}

TEST(Timestamp, ctor_invalid_arg)
{
	EXPECT_THROW(timestamp ts(ts_invalid), Invalid_ts_format);
}

TEST(Loc_name_finder, common) {
	std::istringstream places(places_init_all);

	std::vector<area> areas;

	std::string name;
	double lat1 = 0, lon1 = 0, lat2 = 0, lon2 = 0;

	while (places >> name >> lat1 >> lon1 >> lat2 >> lon2)
	{
		areas.push_back(area({ lat1, lon1 }, { lat2, lon2 }, name));
	}

	location_name_finder name_finder(areas);

	name = name_finder.find_name({10, 10}).value_or("unknown");
	EXPECT_EQ(place1, name + " ");

	name = name_finder.find_name({20, 20}).value_or("unknown");
	EXPECT_EQ(place2, name + " ");

	name = name_finder.find_name({-30, -30}).value_or("unknown");
	EXPECT_EQ(place3, name + " ");

	name = name_finder.find_name({ 0,0 }).value_or("unknown");
	EXPECT_EQ(name, "unknown");
}

TEST(Loc_name_finder, border) {
	std::istringstream in_place2(place2 + place2_range);

	std::string name;
	double lat1, lon1, lat2, lon2;

	ASSERT_TRUE(in_place2 >> name >> lat1 >> lon1 >> lat2 >> lon2);
	area area2({ lat1, lon1 }, { lat2, lon2 }, name);

	location_name_finder name_finder({area2});

	name = name_finder.find_name({ 10, 10 }).value_or("unknown");
	EXPECT_EQ(name, "unknown");

	name = name_finder.find_name({ 20, 20 }).value_or("unknown");
	EXPECT_EQ(place2, name + " ");

	name = name_finder.find_name({ -30, -30 }).value_or("unknown");
	EXPECT_EQ(name, "unknown");

	name = name_finder.find_name({ 0,0 }).value_or("unknown");
	EXPECT_EQ(name, "unknown");
}