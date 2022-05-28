#pragma once
#include <unordered_map>

#include "user_location_ordered_by_time.h"
#include "user_id.h"

class database final
{
	using unordered_map_iterator = std::unordered_map<user_id, user_location_ordered_by_time, user_id_hash>::iterator;
	using unordered_map_const_iterator = std::unordered_map<user_id, user_location_ordered_by_time, user_id_hash>::const_iterator;

	std::unordered_map<user_id, user_location_ordered_by_time, user_id_hash> user_data_by_id_;

public:
	void insert_or_assign(const user_id& id, const timestamp& time, const location& loc);
	void erase(const user_id& id);

	unordered_map_iterator find(const user_id& id);
	unordered_map_iterator begin();
	unordered_map_iterator end();

	unordered_map_const_iterator cfind(const user_id& id) const;
	unordered_map_const_iterator cbegin() const;
	unordered_map_const_iterator cend() const;
};
