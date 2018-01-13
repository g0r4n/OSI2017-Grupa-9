#pragma once

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

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

		Date();
		Date(int, int, int);
		Date(std::string&);
		Date(const Date&);
		~Date();
		bool operator<(const Date&);
		bool operator>(const Date&);
		friend std::ostream& operator<<(std::ostream&, const Date&);
	};

	Bill();
	Bill(std::string customer, Date date, std::vector<Product> products);
	Bill(const Bill&);
	Bill& operator=(const Bill&);
	static void billClassification();
	
	void writeBillToConsole();
	static void split(const std::string& s, char c, std::vector<std::string>& v);
	Date getDate();
	std::vector<Bill::Product> getProductKey();
	std::string getCustomer();
private:
	std::string customer;
	Date date;
	std::vector<Product> products;
	friend std::ostream& operator<<(std::ostream&, const Bill&);
	static int serialNumber;
	static bool validationFormat1(std::ifstream&, Bill&);
	static bool validationFormat2(std::ifstream&, Bill&);
	static bool validationFormat3(std::ifstream&, Bill&);
	static bool validationFormat4(std::ifstream&, Bill&);
	static bool validationFormat5(std::ifstream&, Bill&, std::string, Date);
	static void writeBillToFile(Bill);
	static inline std::string &rtrim(std::string &s);
	static int getFormat(std::ifstream&);
	static void saveFileToObradjeniRacuni(std::string, std::ifstream&, Bill);
	static void saveFileToRacuniSaGreskom(std::string, std::ifstream&);
	static std::string removeDoubleCharacters(std::string, char);
 };
