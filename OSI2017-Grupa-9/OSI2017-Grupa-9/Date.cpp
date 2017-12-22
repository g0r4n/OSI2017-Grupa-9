#include "Date.h"



Date::Date(int d, int m, int y) : day(d), month(m), year(y)
{}

Date::Date(const Date &other)
{
	day = other.day;
	month = other.month;
	year = other.year;
}

Date::Date(std::string& str)
{
	std::vector<std::string> vec;
	split(str, '/', vec);
	day = std::stoi(vec[0]);
	month = std::stoi(vec[1]);
	year = std::stoi(vec[2]);
}

Date::~Date()
{
}

Date & Date::operator=(const Date &other)
{
	if (this != &other)
	{
		day = other.day;
		month = other.month;
		year = other.year;
	}
	return *this;
}

bool Date::operator==(const Date& other)
{
	if (other.day == day && other.month == month && other.year == year)
		return true;
	else
		return false;
}

bool Date::operator!=(const Date &other)
{
	if (!operator==(other))
		return true;
	else return false;
}

bool Date::operator>(const Date &other)
{
	if (year > other.year)
		return true;
	if (month > other.month)
		return true;
	return day > other.day;

}

bool Date::operator<(const Date &other)
{
	if (!operator>(other))
		return true;
	return false;
}

bool Date::operator>=(const Date &other)
{
	if (year > other.year || other.year == year)
		return true;
	if (month > other.month || month == other.month)
		return true;
	return (day > other.day || day == other.day);
}

bool Date::operator<=(const Date &other)
{
	if (year < other.year || other.year == year)
		return true;
	if (month < other.month || month == other.month)
		return true;
	return (day < other.day || day == other.day);
}

void Date::split(const std::string & s, char c, std::vector<std::string>& v)
{
	std::string::size_type i = 0;
	std::string::size_type j = s.find(c);

	while (j != std::string::npos)
	{
		v.push_back(s.substr(i, j-i));
		i = ++j;
		j = s.find(c, j);

		if (j == std::string::npos)
			v.push_back(s.substr(i, s.length()));
	}
}

std::ostream & operator<<(std::ostream &str, const Date &other)
{
	str << other.day << "." << other.month << "." << other.year<<".";
	return str;
}
