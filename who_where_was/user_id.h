#pragma once

class user_id
{
	size_t id_;
public:
	user_id(const size_t id) : id_(id) { }

	size_t get_id() const { return id_; }

	bool operator== (const user_id& rhs) const { return id_ == rhs.get_id(); }
};

class user_id_hash
{
public:
	size_t operator()(const user_id& user) const { return user.get_id(); }
};