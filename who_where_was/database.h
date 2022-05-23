#pragma once
#include <unordered_map>

#include "user_info.h"

class Database final
{
	using unord_map = std::unordered_map<size_t, User_info>;
	using const_it = unord_map::const_iterator;
	using it = unord_map::iterator;

	unord_map users_data_;

public:
	void insert_or_assign(const size_t id, const Time& t, const Location& l);
	void erase(const size_t id);

	it find(const size_t id);
	it begin();
	it end();

	const_it cfind(const size_t id) const;
	const_it cbegin() const;
	const_it cend() const;
};
