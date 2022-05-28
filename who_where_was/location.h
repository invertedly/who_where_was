#pragma once
#include <string>

#include "point.h"

class location final
{
	point coord_;
	std::string name_;
public:
	location(const point& coord, const std::string& name = "") : coord_(coord), name_(name) { }

	const point& get_coord() const { return coord_; }
	const std::string& get_name() const { return name_; }

	void set_name(const std::string& name) { name_ = name; }
};
