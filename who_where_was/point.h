#pragma once

class point final
{
	double lat_;
	double lon_;
public:
	point(const double lat, const double lon) : lat_(lat), lon_(lon) {}

	double get_lat() const { return lat_; }
	double get_lon() const { return lon_; }
};