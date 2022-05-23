#include "database.h"


void Database::insert_or_assign(const size_t id, const Time& t, const Location& l)
{
	users_data_[id].insert_or_assign(t, l);
}

void Database::erase(const size_t id)
{
	users_data_.erase(id);
}

Database::it Database::find(const size_t id)
{
	return users_data_.find(id);
}

Database::it Database::begin()
{
	return users_data_.begin();
}

Database::it Database::end()
{
	return users_data_.end();
}

Database::const_it Database::cfind(const size_t id) const
{
	return users_data_.find(id);
}

Database::const_it Database::cbegin() const
{
	return users_data_.begin();
}

Database::const_it Database::cend() const
{
	return users_data_.end();
}
