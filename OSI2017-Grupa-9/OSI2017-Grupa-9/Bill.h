#pragma once
#include"AssistFunc.h"

namespace fs = std::experimental::filesystem;

class Bill
{
public:
	struct Product
	{
		std::string productKey;
		double soldQuantity, price, sumForProduct;

		Product(std::string, double, double, double);
		friend std::ostream& operator<<(std::ostream&, const Product&);

	};

	struct Date
	{
		int day, month, year;

		Date(int, int, int);
		Date(std::string&);
		Date(const Date&);
		~Date();
		bool operator<(const Date&);
		bool operator>(const Date&);
		friend std::ostream& operator<<(std::ostream&, const Date&);
	};

	Bill(std::string customer, Date date, std::vector<Product> products);
	Bill(const Bill&);
	Bill& operator=(const Bill&);
	static void billClassification();
	static void split(const std::string& s, char c, std::vector<std::string>& v);
private:
	std::string customer;
	Date date;
	std::vector<Product> products;
	friend std::ostream& operator<<(std::ostream&, const Bill&);
	static bool validation(std::ifstream&);
	static void writeBillToFile(std::ifstream&);
	//dodavanje nove funkcionalnosti
	static inline std::string &rtrim(std::string &s);
};
