#pragma once
#include "Bill.h"
#include "Administrator.h"
int Bill::serialNumber = 0;

Bill::Bill() : customer(""), date(1, 1, 1900)
{
}

Bill::Bill(std::string customer, Date date, std::vector<Bill::Product> products) : date(date)
{
	this->customer = customer;
	for (auto& p : products)
		this->products.push_back(p);
}

Bill::Bill(const Bill &other) : date(other.date)
{
	customer = other.customer;
	for (auto &p : other.products)
		this->products.push_back(p);
}

Bill& Bill::operator=(const Bill &other)
{
	if (this != &other)
	{
		customer = other.customer;
		date = other.date;
		for (auto &p : other.products)
			this->products.push_back(p);
	}
	return *this;
}

bool Bill::validationFormat1(std::ifstream& file, Bill &bill) 
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
			productKey = rtrim(vec[0]);
			soldQuantity = std::stod(vec[1]);
			price = std::stod(vec[2]);
			sumForProduct = std::stod(vec[3]);
			if (fabs(soldQuantity * price - sumForProduct) > 0.00001)
				return false;
			products.push_back(Bill::Product(productKey, soldQuantity, price, sumForProduct));
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

		file.clear();
		file.close();

		Bill temp = Bill(customer, date, products);
		bill = temp;

		return true;



	}
	else
		std::cout << "Nije moguce procitati fajl i provjeriti da li je validan" << std::endl;
	return false;
}

bool Bill::validationFormat2(std::ifstream &file, Bill &bill)
{
	std::string tempString;
	std::vector<std::string> vec;
	std::vector<Bill::Product> products;
	std::string customer, productKey;
	double soldQuantity, price, pdv, sum = 0, sumForProduct;

	if (file.is_open())
	{
		for (int i = 0; i < 5; i++)
			std::getline(file, tempString);
		std::getline(file, tempString);
		split(tempString, ' ', vec);
		if (vec[0] != "Kupac:")
			return false;
		customer = vec[1];
		vec.clear();

		for (int i = 0; i < 3; i++)
			std::getline(file, tempString);

		while (std::getline(file, tempString) && tempString != "---------------------------------------")
		{
			split(tempString, '-', vec);
			productKey = rtrim(vec[0]);
			soldQuantity = std::stod(vec[1]);
			price = std::stod(vec[2]);
			sumForProduct = std::stod(vec[3]);
			if (fabs(soldQuantity * price - sumForProduct) > 0.00001)
				return false;
			products.push_back(Bill::Product(productKey, soldQuantity, price, sumForProduct));
			sum += sumForProduct;
			vec.clear();
		}

		std::getline(file, tempString);
		std::getline(file, tempString);
		split(tempString, ' ', vec);
		if (fabs(std::stod(vec[1]) - sum) > 0.00001)
			return false;
		vec.clear();

		std::getline(file, tempString);
		split(tempString, ' ', vec);
		pdv = std::stod(vec[1]);
		if (fabs(pdv - sum * 0.17) > 0.00001)
			return false;
		vec.clear();

		std::getline(file, tempString);
		split(tempString, ' ', vec);
		double sumBill = std::stod(vec[3]);
		double sumAndPdv = sum + pdv;
		if (fabs(sumBill - sumAndPdv) > 0.00001)
			return false;
		vec.clear();

		std::getline(file, tempString);
		split(tempString, ' ', vec);
		Date date(vec[1]);
		time_t t = time(0);
		struct tm * now = localtime(&t);
		Date current(now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);
		if (date > current)
			return false;

		bill = Bill(customer, date, products);
		file.close();
		return true;
	}

	return false;
}

bool Bill::validationFormat3(std::ifstream &file, Bill &bill)
{
	std::string tempString, line;
	std::vector<std::string> vec;
	std::vector<Bill::Product> products;
	std::string customer, productKey;
	double soldQuantity, price, sumForProduct, sum = 0, pdv;

	if (file.is_open())
	{
		std::getline(file, tempString);
		std::getline(file, tempString);

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
		for (int i = 0; i < 5; i++)
			std::getline(file, tempString);
		vec.clear();

		while (std::getline(file, tempString) && tempString != "----------------------------------")
		{
			line = removeDoubleCharacters(tempString, '=');
			split(line, '=', vec);
			productKey = rtrim(vec[0]);
			soldQuantity = std::stod(vec[1]);
			price = std::stod(vec[2]);
			sumForProduct = std::stod(vec[3]);
			if (fabs(soldQuantity * price - sumForProduct) > 0.00001)
				return false;
			sum += sumForProduct;
			products.push_back(Bill::Product(productKey, soldQuantity, price, sumForProduct));
			vec.clear();
		}

		std::getline(file, tempString);

		std::string sumOnBill, pdvOnBill;

		std::getline(file, tempString);
		split(tempString, '\t', vec);
		sumOnBill = vec[0];
		pdvOnBill = vec[2];
		vec.clear();

		split(sumOnBill, ' ', vec);
		if (fabs(std::stod(vec[1]) - sum) > 0.00001)
			return false;
		vec.clear();

		split(pdvOnBill, ' ', vec);
		pdv = std::stod(vec[1]);
		if (fabs(pdv - sum * 0.17) > 0.00001)
			return false;
		vec.clear();

		std::getline(file, tempString);
		std::getline(file, tempString);

		split(tempString, ' ', vec);
		double sumBill = std::stod(vec[3]);
		double sumAndPdv = sum + pdv;
		if (fabs(sumBill - sumAndPdv) > 0.00001)
			return false;

		bill = Bill(customer, date, products);
		file.close();
		return true;
	}

	return false;
}

bool Bill::validationFormat4(std::ifstream &file, Bill &bill)
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

		for (int i = 0; i<5; i++)
			std::getline(file, tempString);

		while (std::getline(file, tempString) && tempString != "---------------------------------------")
		{
			vec.clear();
			split(tempString, '-', vec);
			productKey = rtrim(vec[0]);
			soldQuantity = std::stod(vec[1]);
			price = std::stod(vec[2]);
			sumForProduct = std::stod(vec[3]);
			if (fabs(soldQuantity * price - sumForProduct) > 0.00001)
				return false;
			products.push_back(Bill::Product(productKey, soldQuantity, price, sumForProduct));
			sum += sumForProduct;
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
		std::getline(file, tempString);
		vec.clear();
		split(tempString, ' ', vec);

		double sumBill = std::stod(vec[3]);
		double sumAndPdv = sum + pdv;

		if (fabs(sumBill - sumAndPdv) > 0.00001)
			return false;

		file.clear();
		file.close();

		bill = Bill(customer, date, products);

		return true;

	}

	return false;
}

bool Bill::validationFormat5(std::ifstream &file, Bill &bill, std::string customer, Date date)
{
	std::string tempString;
	std::vector<std::string> vec;
	std::vector<Bill::Product> products;
	std::string productKey;
	double soldQuantity, price, sumForProduct;

	time_t t = time(0);
	struct tm * now = localtime(&t);
	Date current(now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);

	if (date > current)
		return false;

	if (file.is_open())
	{
		std::getline(file, tempString);
		split(tempString, ',', vec);
		if (vec[0] != "Sifra" || vec[1] != "Kolicina" || vec[2] != "Cijena" || vec[3] != "Ukupno")
			return false;
		vec.clear();
		while (std::getline(file, tempString))
		{
			split(tempString, ',', vec);
			productKey = rtrim(vec[0]);
			soldQuantity = std::stod(vec[1]);
			price = std::stod(vec[2]);
			sumForProduct = std::stod(vec[3]);
			if (fabs(soldQuantity * price - sumForProduct) > 0.00001)
				return false;
			products.push_back(Bill::Product(productKey, soldQuantity, price, sumForProduct));
			vec.clear();
		}
		bill = Bill(customer, date, products);
		return true;
	}

	return false;
}


void Bill::writeBillToFile(Bill bill)
{
	std::ofstream fileToWrite;

	fileToWrite.open("Racuni za ispis.txt", std::ios::out | std::ios::app);
	fileToWrite << bill;
	fileToWrite.close();
}

inline std::string & Bill::rtrim(std::string & s)
{
	s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	return s;
}

int Bill::getFormat(std::ifstream &file)
{
	std::string line;
	std::vector<std::string> vec;


	if (file.is_open())
	{
		std::getline(file, line);
		split(line, ' ', vec);
		if (vec[0] == "Kupac:")
		{
			vec.clear();
			while (std::getline(file, line));
			if (line == "=======================================")
				return 4;
			split(line, ' ', vec);
			if (vec[0] == "Ukupno")
				return 1;
			else
				return 0;
		}
		else
		{
			vec.clear();
			while (std::getline(file, line));
			split(line, ' ', vec);
			if (vec[0] == "Datum:")
				return 2;
			else if (vec[0] == "Ukupno")
				return 3;
			else
				return 0;
		}
	}
	return 0;
}

void Bill::saveFileToObradjeniRacuni(std::string path, std::ifstream &file, Bill bill)
{
	std::vector<std::string> vec;
	std::string pathToSave;

	split(path, '\\', vec);
	pathToSave = "Obradjeni racuni\\" + vec[1];

	if (fs::is_directory(pathToSave) == false)
		fs::create_directory("Obradjeni racuni");

	try
	{
		fs::copy_file(fs::path(path), pathToSave);
		writeBillToFile(bill);
		serialNumber++;
	}
	catch (const fs::v1::filesystem_error &e)
	{

	}
}

void Bill::saveFileToRacuniSaGreskom(std::string path, std::ifstream &file)
{
	std::string pathToSave;
	std::string renameBill;
	std::vector<std::string> vec, vecError;

	split(path, '\\', vec);
	split(vec[1], '.', vecError);
	if (vecError[1] == "txt")
		renameBill = vecError[0] + "_error." + vecError[1];
	else
		renameBill = vecError[0] + "." + vecError[1] + "." + vecError[2] + "_error." + vecError[3];
	pathToSave = "Racuni sa greskom\\" + renameBill;

	if (fs::is_directory(pathToSave) == false)
		fs::create_directory("Racuni sa greskom");

	try
	{
		fs::copy_file(fs::path(path), pathToSave);
		cout << "Doslo je do greske pri obradi racuna '" << renameBill << " '. Racun je sacuvan u folderu 'Racuni sa greskom'." << endl;
	}
	catch (const fs::v1::filesystem_error &e)
	{

	}
}

std::string Bill::removeDoubleCharacters(std::string str, char c)
{
	std::string res = "";
	for (unsigned int i = 0; i < str.size(); i++)
	{
		if (str[i] == c && str[i + 1] == c)
			continue;
		else
			res.push_back(str[i]);
	}
	return res;
}


void Bill::writeBillToConsole()
{
	double sum = 0;
	
	cout << std::resetiosflags(std::ios::adjustfield); 
	cout << std::setiosflags(std::ios::left);
	cout.fill(' ');
	cout << std::setfill(' ') << std::setw(20)<< this->getDate() <<"    " << std::setfill(' ')
		<< std::setw(20) << this->getCustomer()
		<< std::setw(19) << this->getProductKey()[0].productKey
		<< std::setw(10) << std::to_string(this->getProductKey()[0].price).substr(0, 4) + admin::getCurrentCurrency()
		<< std::setw(10) << (std::to_string((this->getProductKey()[0].price) * PDV)).substr(0, 4) + admin::getCurrentCurrency()
		<< std::setw(10) << this->getProductKey()[0].soldQuantity
		<< std::setw(10) << std::to_string(this->getProductKey()[0].price*this->getProductKey()[0].soldQuantity).substr(0, 4) + admin::getCurrentCurrency() //potencijalna greska(kod ispisa) gdje ne ispise decimalni dio izraza
		<< std::setw(10) << std::to_string(this->getProductKey()[0].price*this->getProductKey()[0].soldQuantity+this->getProductKey()[0].price*this->getProductKey()[0].soldQuantity*PDV).substr(0, 4) + admin::getCurrentCurrency() <<endl;
	sum += this->getProductKey()[0].price*this->getProductKey()[0].soldQuantity;
	for (int i = 1;i < this->getProductKey().size();i++)
	{
		cout << std::setfill(' ') << std::setw(20) <<  "    " << std::setfill(' ') << std::setw(15) << " " 
			<< std::setw(19) << this->getProductKey()[i].productKey
			<< std::setw(10) << std::to_string(this->getProductKey()[i].price).substr(0, 4) + admin::getCurrentCurrency()
			<< std::setw(10) << (std::to_string((this->getProductKey()[i].price) * PDV)).substr(0, 4) + admin::getCurrentCurrency()
			<< std::setw(10) << this->getProductKey()[i].soldQuantity
			<< std::setw(10) << std::to_string(this->getProductKey()[i].price*this->getProductKey()[i].soldQuantity).substr(0, 4) + admin::getCurrentCurrency()
			<< std::setw(10) << std::to_string(this->getProductKey()[i].price*this->getProductKey()[i].soldQuantity + this->getProductKey()[i].price*this->getProductKey()[i].soldQuantity*PDV).substr(0, 4) + admin::getCurrentCurrency() << endl;
		sum += this->getProductKey()[i].price*this->getProductKey()[i].soldQuantity;
	}
	
	cout << std::setfill(' ') << std::setw(112) << " ";
	cout << std::setfill(' ') <<endl << std::setw(86)<<" " <<"Ukupno: " << sum << admin::getCurrentCurrency().substr(0,2) << endl;
	cout << std::setfill(' ') << endl << std::setw(86) << " " << "PDV: " << sum*PDV << admin::getCurrentCurrency().substr(0, 2) << endl;
	sum *= 1 + PDV;
	cout << std::setfill(' ') << endl << std::setw(86) << " " << "Ukupno za placanje: " << sum << admin::getCurrentCurrency().substr(0, 2) << endl << std::setfill('=') << std::setw(112) << " " <<endl << endl << endl <<endl;
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

Bill::Date Bill::getDate()
{
	return this->date;
}

std::vector<Bill::Product> Bill::getProductKey()
{
	return this->products;
}

std::string Bill::getCustomer()
{
	return this->customer;
}


void Bill::billClassification()
{
	int format = 0;
	int tempNum;
	std::string temp;
	std::vector<std::string> strings;

	std::ifstream configFile(ConfigFile);
	std::getline(configFile, temp);
	split(temp, '=', strings);
	configFile.seekg(0, configFile.beg);


	serialNumber = std::stoi(strings[1]);
	tempNum = serialNumber;

	for (auto& p : fs::directory_iterator("Neobradjeni racuni"))
	{
		if (p.path().extension() == ".txt")
		{

			auto f = std::ifstream(p.path().c_str());

			format = getFormat(f);

			f.clear();
			f.seekg(0, f.beg);

			Bill bill;

			switch (format)
			{
			case 1:
				if (validationFormat1(f, bill))
					saveFileToObradjeniRacuni(p.path().string(), f, bill);
				else
					saveFileToRacuniSaGreskom(p.path().string(), f);
				break;
			case 2:
				if (validationFormat2(f, bill))
					saveFileToObradjeniRacuni(p.path().string(), f, bill);
				else
					saveFileToRacuniSaGreskom(p.path().string(), f);
				break;
			case 3:
				if (validationFormat3(f, bill))
					saveFileToObradjeniRacuni(p.path().string(), f, bill);
				else
					saveFileToRacuniSaGreskom(p.path().string(), f);
				break;
			case 4:
				if (validationFormat4(f, bill))
					saveFileToObradjeniRacuni(p.path().string(), f, bill);
				else
					saveFileToRacuniSaGreskom(p.path().string(), f);
				break;
			default:
				saveFileToRacuniSaGreskom(p.path().string(), f);
			}

		}
		else if (p.path().extension() == ".csv")
		{
			auto f = std::ifstream(p.path().c_str());

			std::string customer, tempString = p.path().string();
			std::vector<std::string> vec;
			Bill bill;

			split(tempString, '\\', vec);
			tempString = vec[1];
			vec.clear();

			split(tempString, '#', vec);
			customer = vec[0];
			tempString = vec[1];
			vec.clear();

			split(tempString, '.', vec);
			int day = std::stoi(vec[0]);
			int mon = std::stoi(vec[1]);
			int year = std::stoi(vec[2]);
			Date date(day, mon, year);
			vec.clear();
			if (validationFormat5(f, bill, customer, date))
				saveFileToObradjeniRacuni(p.path().string(), f, bill);
			else
				saveFileToRacuniSaGreskom(p.path().string(), f);
		}
	}
	for (auto& p : fs::directory_iterator("Neobradjeni racuni"))
	{
		fs::remove(p.path());
	}

	std::ofstream outputFile("OtherFile.txt");
	std::string lineToReplace("#static int serialNumber = " + std::to_string(tempNum));
	std::string newLine("#static int serialNumber = " + std::to_string(serialNumber));
	while (std::getline(configFile, temp))
	{
		if (temp == lineToReplace)
			temp = newLine;
		temp += "\n";
		outputFile << temp;
	}

	outputFile.flush();
	configFile.close();
	outputFile.close();

	std::remove(ConfigFile);
	std::rename("OtherFile.txt", ConfigFile);
}

std::ostream& operator<<(std::ostream& str, const Bill& bill)
{
	for (auto& p : bill.products)
	{
		str << bill.date << "#" << bill.customer << "#" << p << "#" <<  Bill::serialNumber << "#" << bill.products.size() <<std::endl;
	}
	return str;
}

Bill::Product::Product(std::string productKey, double soldQuantity, double price, double sumForProduct) : productKey(productKey), soldQuantity(soldQuantity),
price(price), sumForProduct(sumForProduct)
{

}

Bill::Date::Date()
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
	else if (year == other.year && month > other.month)
		return true;
	else if (year == other.year && month == other.month && day > other.day)
		return true;
	return false;
}

bool Bill::Date::operator<(const Bill::Date& other)
{
	if (year < other.year)
		return true;
	else if (year == other.year && month < other.month)
		return true;
	else if (year == other.year && month == other.month && day < other.day)
		return true;
	return false;
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