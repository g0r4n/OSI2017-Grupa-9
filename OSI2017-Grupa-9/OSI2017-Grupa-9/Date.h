#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <functional>

class Date
{
public:
	Date(int, int, int);
	Date(std::string&);
	Date(const Date&);
	~Date();
	Date& operator=(const Date&);
	bool operator==(const Date&);
	bool operator!=(const Date&);
	bool operator>(const Date&);
	bool operator<(const Date&);
	bool operator>=(const Date&);
	bool operator<=(const Date&);
	static void split(const std::string& s, char c, std::vector<std::string>& v);
	
private:
	int day, month, year;
	friend std::ostream& operator<<(std::ostream&, const Date&);
	//void split(const std::string& s, char c, std::vector<std::string>& v);
};