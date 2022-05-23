#pragma once
#include <string>

#include "coord.h"

class Location final
{
	Coord coord_;
	std::string name_;
public:
	Location(const Coord& coord, const std::string& name = "") : coord_(coord), name_(name) { }

	Coord get_coord() const { return coord_; }
	std::string get_name() const { return name_; }

	void set_name(const std::string& name) { name_ = name; }
};
