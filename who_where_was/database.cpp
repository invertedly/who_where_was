#include "database.h"

void database::insert_or_assign(const user_id& id, const timestamp& time, const location& loc)
{
	user_data_by_id_[id].insert_or_assign(time, loc);
}

void database::erase(const user_id& id)
{
	user_data_by_id_.erase(id);
}

database::unordered_map_iterator database::find(const user_id& id)
{
	return user_data_by_id_.find(id);
}

database::unordered_map_iterator database::begin()
{
	return user_data_by_id_.begin();
}

database::unordered_map_iterator database::end()
{
	return user_data_by_id_.end();
}

database::unordered_map_const_iterator database::cfind(const user_id& id) const
{
	return user_data_by_id_.find(id);
}

database::unordered_map_const_iterator database::cbegin() const
{
	return user_data_by_id_.begin();
}

database::unordered_map_const_iterator database::cend() const
{
	return user_data_by_id_.end();
}
