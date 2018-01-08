#include "User.h"
using namespace user;


string user::User::getUserName() const
{
	return std::get<0>(userInfo);
}

void user::User::setUserName(const string& newUserName)
{
	std::get<0>(userInfo) = newUserName;
}

void user::User::setName(const string &newName)
{
	std::get<1>(userInfo) = newName;
}

void user::User::setSureName(const string &newSureName)
{
	std::get<2>(userInfo) = newSureName;
}

void user::User::setPIN(const string &newPin)
{
	std::get<3>(userInfo) = newPin;
}

void user::User::setUserGroup(const bool &newUserGroup)
{
	std::get<4>(userInfo) = newUserGroup;
}

User::User(){}

user::User::User(const std::tuple<string,string, string, string, bool>& userInfo)
{
	this->userInfo = userInfo;
}

User::~User(){}

bool user::User::operator<(const User& other) const
{
	if (std::get<1>(userInfo) < std::get<1>(other.userInfo))
		return true;
	else if (std::get<1>(userInfo) == std::get<1>(other.userInfo))
		if (std::get<2>(userInfo) < std::get<2>(other.userInfo))
			return true;
		else if (std::get<2>(userInfo) == std::get<2>(other.userInfo))
			if (std::get<0>(userInfo) < std::get<0>(other.userInfo))
				return true;
	return false;
}

bool user::User::operator>(const User& other) const
{
	return !((*this) < other);
}

bool user::User::operator==(const User &other) const
{
	if (std::get<0>(userInfo) == std::get<0>(other.userInfo)) return true;
	return false;
}

void user::User::print(std::ostream& stream) const
{
	stream << std::resetiosflags(std::ios::adjustfield);			// resetovanje 
	stream << std::setiosflags(std::ios::left);					// poravnanje u lijevo
	stream
		<< std::setw(16)
		<< std::get<0>(userInfo)
		<< " "
		<< std::setw(16)
		<< std::get<1>(userInfo)
		<< " "
		<< std::setw(16)
		<< std::get<2>(userInfo) 
		<< " " 
		<< std::setw(5)
		<< std::get<3>(userInfo) 
		<< " " 
		//<<std::setw(4)
		<< std::get<4>(userInfo);
}

void user::User::read(std::istream& stream)
{
	stream
		>> std::get<0>(userInfo) 
		>> std::get<1>(userInfo) 
		>> std::get<2>(userInfo) 
		>> std::get<3>(userInfo)
		>> std::get<4>(userInfo);
}



