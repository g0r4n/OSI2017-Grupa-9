#pragma once

#include <string>
#include <experimental\filesystem>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <ctime>
#include <exception>



#include "Date.h"

namespace fs = std::experimental::filesystem; //upotreba radi lakseg koristenja da se ne pise svaki put std::experimetal::filesystem

class Bill
{
public:
	Bill(std::string, Date, std::string, double, double, double, double);
	Bill(const Bill&);
	Bill& operator=(const Bill&);
	static void billClassification();
private:
	std::string customer, productKey;
	Date date;
	double soldQuantity, price, priceToPay, pdv;
	friend std::ostream& operator<<(std::ostream&, const Bill&); // radi testiranja funkcija koja ispisuje racun
	static bool validation(std::ifstream&);
};
