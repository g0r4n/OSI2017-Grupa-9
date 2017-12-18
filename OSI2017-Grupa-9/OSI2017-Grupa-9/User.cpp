#include "User.h"
using namespace user;


User::User(){}

user::User::User(const std::tuple<string, string, string, bool>& userInfo)
{
	this->userInfo = userInfo;
}

User::~User(){}

bool user::User::operator<(const User& other) const
{
	if (std::get<0>(userInfo) < std::get<0>(other.userInfo))
		return true;
	else if (std::get<0>(userInfo) == std::get<0>(other.userInfo))
		if (std::get<1>(userInfo) < std::get<1>(other.userInfo))
			return true;
	return false;
}

bool user::User::operator>(const User& other) const
{
	return !((*this) < other);
}

bool user::User::operator==(const User &other) const
{
	if (std::get<0>(userInfo) == std::get<0>(other.userInfo) && std::get<1>(userInfo) == std::get<1>(other.userInfo)) return true;
	return false;
}

void user::User::print(std::ostream& stream) const
{
	stream << std::get<0>(userInfo) << " " << std::get<1>(userInfo) << " " << std::get<2>(userInfo) << " " << std::get<3>(userInfo);
}

void user::User::read(std::istream& stream)
{
	stream >> std::get<0>(userInfo) >> std::get<1>(userInfo) >> std::get<2>(userInfo) >> std::get<3>(userInfo);
}



