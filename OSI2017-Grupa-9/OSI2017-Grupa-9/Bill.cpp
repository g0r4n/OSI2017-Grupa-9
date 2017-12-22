#include "Bill.h"

Bill::Bill(std::string customer, Date date, std::string productKey, double soldQuantity, double price, double priceToPay, double pdv) :
	customer(customer), date(date), productKey(productKey), soldQuantity(soldQuantity), price(price), priceToPay(priceToPay), pdv(pdv)
{}

Bill::Bill(const Bill &other) : date(other.date)
{
	customer = other.customer;
	productKey = other.productKey;
	soldQuantity = other.soldQuantity;
	price = other.price;
	priceToPay = other.priceToPay;
	pdv = other.pdv;
}

Bill & Bill::operator=(const Bill &other)
{
	if (this != &other)
	{
		customer = other.customer;
		date = other.date;
		soldQuantity = other.soldQuantity;
		productKey = other.productKey;
		price = other.price;
		priceToPay = other.priceToPay;
		pdv = other.pdv;
	}
	return *this;
}

bool Bill::validation(std::ifstream& file) // provjerava da li je racun validan za format 1 
{
	std::string tempString;
	std::vector<std::string> vec;
	std::string customer, productKey;
	double soldQuantity, price, pdv, sum = 0;

	std::vector<Bill> list;
	
	if (file.is_open())
	{
		std::getline(file, tempString);
		Date::split(tempString, ' ', vec);
		if (vec[0] != "Kupac:")
			return false;
		customer = vec[1];
		vec.clear();

		std::getline(file, tempString);
		Date::split(tempString, ' ', vec);
		Date date(vec[1]);

		time_t t = time(0);
		struct tm * now = localtime(&t);
		Date current(now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);

		if (date < current)
			return false;

		for (int i = 0; i < 4; i++)
			std::getline(file, tempString);

		while (std::getline(file, tempString) && tempString != "---------------------------------------")
		{
			vec.clear();
			Date::split(tempString, '-', vec);
			productKey = vec[0];
			soldQuantity = std::stod(vec[1]);
			price = std::stod(vec[2]);
			if (soldQuantity * price != std::stod(vec[3]))
				return false;
			sum += std::stod(vec[3]);

		}

		vec.clear();
		std::getline(file, tempString);
		Date::split(tempString, ' ', vec);

		if (std::stod(vec[1]) != sum)
			return false;

		std::getline(file, tempString);
		vec.clear();
		Date::split(tempString, ' ', vec);
		pdv = std::stod(vec[1]);

		std::getline(file, tempString);
		vec.clear();
		Date::split(tempString, ' ', vec);

		if (std::stod(vec[3]) != sum + pdv)
			return false;
		else return true;


		file.close();
	}
	else
		std::cout << "Nije moguce procitati fajl i provjeriti da li je validan" << std::endl;
	return false;
}


void Bill::billClassification()
{
	//provjera funkcije koja pravi novi folder

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
					Date::split(fileName, '\\', vec);
					pathToSave = tempPath + vec[1];
					if (fs::is_directory(pathToSave) == false)
						fs::create_directory("Obradjeni racuni");



					try
					{

						fs::copy_file(p.path(), pathToSave);
					}
					catch (const std::experimental::filesystem::v1::filesystem_error &e)
					{
						std::cout <<"Error: "<< e.what()<<std::endl;
					}

				}
				else
				{
					fileName = p.path().string();
					Date::split(fileName, '\\', vec);
					Date::split(vec[1], '.', vecError);
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
						std::cout << "Error: pokusaj obrade vec obradjenog racuna" << std::endl << e.what()<< std::endl;
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
	str << "Kupac: " << bill.customer << std::endl << "-Datum: " << bill.date << std::endl << "-Prodana kolicina: " << bill.soldQuantity << std::endl << "-Sifra proizvoda: " << bill.productKey << std::endl;
	str << "-Cijena jednog proizvoda: " << bill.price << std::endl << "-Cijena za placanje: " << bill.priceToPay << std::endl << "-PDV: " << bill.pdv<<std::endl;
	return str;
}