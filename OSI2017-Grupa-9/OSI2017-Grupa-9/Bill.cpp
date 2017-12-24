#include "Bill.h"

Bill::Bill(std::string customer, Date date, std::vector<Bill::Product> products) : date(date)
{
	this->customer = customer;
	for (auto& p : products)
		this->products.push_back(p);
}

Bill::Bill(const Bill &other) : date(other.date)
{
	customer = other.customer;
	std::copy(products.begin(), products.end(), this->products.begin());
}

Bill & Bill::operator=(const Bill &other)
{
	if (this != &other)
	{
		customer = other.customer;
		date = other.date;
		std::copy(products.begin(), products.end(), this->products.begin());
	}
	return *this;
}

bool Bill::validation(std::ifstream& file) // provjerava da li je racun validan za format 1 
{
	std::string tempString;
	std::vector<std::string> vec;
	std::vector<Bill::Product> products;
	std::string customer, productKey;
	double soldQuantity, price, pdv, sum = 0, sumForProduct;

	if (file.is_open())
	{
		std::getline(file, tempString);
		split(tempString, ' ', vec);
		if (vec[0] != "Kupac:")
			return false;
		customer = vec[1];
		vec.clear();

		std::getline(file, tempString);
		split(tempString, ' ', vec);
		Date date(vec[1]);

		time_t t = time(0);
		struct tm * now = localtime(&t);
		Date current(now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);

		if (date > current)
			return false;

		for (int i = 0; i < 4; i++)
			std::getline(file, tempString);

		while (std::getline(file, tempString) && tempString != "---------------------------------------")
		{
			vec.clear();
			split(tempString, '-', vec);
			productKey = vec[0];
			soldQuantity = std::stod(vec[1]);
			price = std::stod(vec[2]);
			sumForProduct = std::stod(vec[3]);
			if (fabs(soldQuantity * price - sumForProduct) > 0.00001)
				return false;
			sum += std::stod(vec[3]);

		}

		vec.clear();
		std::getline(file, tempString);
		split(tempString, ' ', vec);

		if (fabs(std::stod(vec[1]) - sum) > 0.00001)
			return false;

		std::getline(file, tempString);
		vec.clear();
		split(tempString, ' ', vec);
		pdv = std::stod(vec[1]);

		if (fabs(pdv - sum * 0.17) > 0.00001)
			return false;

		std::getline(file, tempString);
		vec.clear();
		split(tempString, ' ', vec);

		double sumBill = std::stod(vec[3]);
		double sumAndPdv = sum + pdv;

		if (fabs(sumBill - sumAndPdv) > 0.00001)
			return false;


		std::ofstream file;
		file.clear();
		file.close();

		return true;



	}
	else
		std::cout << "Nije moguce procitati fajl i provjeriti da li je validan" << std::endl;
	return false;
}

void Bill::writeBillToFile(std::ifstream &file) // za format1 
{
	std::vector<std::string> vec;

	std::vector<Bill::Product> products;
	std::string lineOfFile;
	std::string customer, productKey;
	double soldQuantity, price, sumForProduct;

	file.seekg(0, file.beg);

	if (file.is_open())
	{

		std::getline(file, lineOfFile);
		split(lineOfFile, ' ', vec);
		customer = vec[1];
		vec.clear();

		std::getline(file, lineOfFile);
		split(lineOfFile, ' ', vec);
		Date date(vec[1]);
		vec.clear();

		for (int i = 0; i < 4; i++)
			std::getline(file, lineOfFile);

		while (std::getline(file, lineOfFile) && lineOfFile != "---------------------------------------")
		{
			split(lineOfFile, '-', vec);
			productKey = rtrim(vec[0]);
			soldQuantity = std::stod(vec[1]);
			price = std::stod(vec[2]);
			sumForProduct = std::stod(vec[3]);

			products.push_back(Bill::Product(productKey, soldQuantity, price, sumForProduct));
			vec.clear();
		}

		std::ofstream fileToWrite;

		fileToWrite.open("Racuni za ispis.txt", std::ios::out | std::ios::app);
		fileToWrite << Bill(customer, date, products);
		fileToWrite.close();
	}
}

inline std::string & Bill::rtrim(std::string & s)
{
	s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	return s;
}

void Bill::split(const std::string & s, char c, std::vector<std::string>& v)
{
	std::string::size_type i = 0;
	std::string::size_type j = s.find(c);

	while (j != std::string::npos)
	{
		v.push_back(s.substr(i, j - i));
		i = ++j;
		j = s.find(c, j);

		if (j == std::string::npos)
			v.push_back(s.substr(i, s.length()));
	}
}


void Bill::billClassification()
{
	std::string tempPath("Obradjeni racuni\\");
	std::string tempPathError("Racuni sa greskom\\");
	std::string fileName, pathToSave, renameBill;
	std::vector<std::string> vec, vecError;


	for (auto& p : fs::directory_iterator("Neobradjeni racuni"))
	{
		if (p.path().extension() == ".txt")
		{
			auto f = std::ifstream(p.path().c_str());

			if (validation(f))
			{
				fileName = p.path().string();
				split(fileName, '\\', vec);
				pathToSave = tempPath + vec[1];
				if (fs::is_directory(pathToSave) == false)
					fs::create_directory("Obradjeni racuni");



				try
				{

					fs::copy_file(p.path(), pathToSave);
					writeBillToFile(f);
				}
				catch (const std::experimental::filesystem::v1::filesystem_error &e)
				{
					std::cout << "Error: " << e.what() << std::endl;
				}

			}
			else
			{
				fileName = p.path().string();
				split(fileName, '\\', vec);
				split(vec[1], '.', vecError);
				renameBill = vecError[0] + "_error." + vecError[1];
				pathToSave = tempPathError + renameBill;
				if (fs::is_directory(pathToSave) == false)
					fs::create_directory("Racuni sa greskom");

				try
				{
					fs::copy_file(p.path(), pathToSave);
				}
				catch (const std::experimental::filesystem::filesystem_error &e)
				{
					std::cout << "Error: pokusaj obrade vec obradjenog racuna" << std::endl << e.what() << std::endl;
				}
			}

		}
		vec.clear();
	}
	for (auto& p : fs::directory_iterator("Neobradjeni racuni"))
	{
		fs::remove(p.path());
	}

}

std::ostream& operator<<(std::ostream& str, const Bill& bill)
{
	for (auto& p : bill.products)
	{
		str << bill.date << "#" << bill.customer << "#" << p << std::endl;
	}
	return str;
}

Bill::Product::Product(std::string productKey, double soldQuantity, double price, double sumForProduct) : productKey(productKey), soldQuantity(soldQuantity),
price(price), sumForProduct(sumForProduct)
{

}

Bill::Date::Date(int day, int month, int year) : day(day), month(month), year(year)
{

}

Bill::Date::Date(std::string &str)
{
	std::vector<std::string> vec;
	split(str, '/', vec);
	day = std::stoi(vec[0]);
	month = std::stoi(vec[1]);
	year = std::stoi(vec[2]);
}

Bill::Date::Date(const Date& other)
{
	day = other.day;
	month = other.month;
	year = other.year;
}

Bill::Date::~Date()
{

}

bool Bill::Date::operator>(const Bill::Date &other)
{
	if (year > other.year)
		return true;
	if (month > other.month)
		return true;
	return day > other.day;
}

bool Bill::Date::operator<(const Bill::Date& other)
{
	if (year < other.year)
		return true;
	if (month < other.month)
		return true;

	return day < other.day;
}


std::ostream & operator<<(std::ostream &str, const Bill::Product &pr)
{
	str << pr.productKey << "#" << pr.soldQuantity << "#" << pr.price << "#" << pr.sumForProduct;
	return str;
}

std::ostream& operator<<(std::ostream &str, const Bill::Date &date)
{
	str << std::setw(2) << std::setfill('0') << date.day << "/" << std::setw(2) << std::setfill('0') << date.month << "/";
	str << std::setw(2) << std::setfill('0') << date.year << ".";
	return str;
}