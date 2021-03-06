#include "Analiticar.h"
#include "Bill.h"
#include <string.h>
#include "Administrator.h"


analiticar::Analiticar::Analiticar() {}

analiticar::Analiticar::Analiticar(const std::tuple<string, string, string, string, bool>& userInfo) : user::User(userInfo) {}

analiticar::Analiticar::~Analiticar() {}

Bill::Date returnDateFromReadString(string input)
{
	string d, m, g;
	d += input[0]; d += input[1];
	m += input[3]; m += input[4];
	g += input[6]; g += input[7]; g += input[8]; g += input[9];
	Bill::Date that(std::stoi(d), std::stoi(m), std::stoi(g));
	return that;
}



Bill returnBillFromReadString(string input) //rijeseno na bolji nacin, deprecated
{
	string customer, productS, ammountStr, priceStr;	//string->bill converter dd/mm/gggg.#buyer#product 123#ammount#price#total
	int buy = 12, prod, amm, pri;
	for (; input[buy] != '#'; buy++)
		customer += input[buy];
	prod = buy + 1;
	for (; input[prod] != '#'; prod++)
		productS += input[prod];
	amm = prod + 1;
	for (; input[amm] != '#'; amm++)
		ammountStr += input[amm];
	pri = amm + 1;
	for (; input[pri] != '#'; pri++)
		priceStr += input[pri];
	std::vector<Bill::Product> temp; temp.push_back(Bill::Product(productS, std::stod(ammountStr), std::stod(priceStr), std::stod(priceStr)*std::stod(ammountStr)));
	return Bill(customer, returnDateFromReadString(input), temp);

}

void analiticar::Analiticar::billsDateOverview()
{
	bool quit = 0;
	std::vector<string> help;
	while (!quit)
	{
		cout << "Unesite pocetni datum u obliku dd/mm/gggg:" << endl;
		string temp;
		std::getline(cin, temp);
		int count = 0;
		for (int i = 0; temp[i]; i++)
			if (temp[i] == '/')
				count++;
		if (temp.length() != 10 || count != 2)
		{
			cout << "Datum nije ispravan" << endl; 
			quit = 0;
		}
		else
		{
			help.clear();
			Bill::split(temp, '/', help);
			if (isdigit(help[0][0]) && isdigit(help[0][1]) && isdigit(help[1][0]) && isdigit(help[1][1]) && isdigit(help[2][0]) && isdigit(help[2][1]) && isdigit(help[2][2]) && isdigit(help[2][3]) && isDateValid(std::stoi(help[1]), std::stoi(help[0]), std::stoi(help[2]))) //provjera jesu svi clanovi digiti
			{
				
				quit = 1;
			}
			else cout << "Datum nije ispravan"<<endl;
		}
		
	}
	Bill::Date start(std::stoi(help[0]), std::stoi(help[1]), std::stoi(help[2]));
	cout << endl<< endl;
	quit = 0;
	help.clear();
	while (!quit)
	{
		cout << "Unesite krajnji datum u obliku dd/mm/gggg:" << endl;
		string temp;
		std::getline(cin, temp);
		int count =0;
		for (int i = 0; temp[i]; i++)
			if (temp[i] == '/')
				count++;
		if (temp.length() != 10 || count != 2)
		{
			cout << "Datum nije ispravan"<<endl;
			quit = 0;
		}
		else
		{
			help.clear();
			Bill::split(temp, '/', help);
			if (isdigit(help[0][0]) && isdigit(help[0][1]) && isdigit(help[1][0]) && isdigit(help[1][1]) && isdigit(help[2][0]) && isdigit(help[2][1]) && isdigit(help[2][2]) && isdigit(help[2][3]) && isDateValid(std::stoi(help[1]), std::stoi(help[0]), std::stoi(help[2])))
			{
				
				quit = 1;
			}
			else cout << "Datum nije ispravan"<<endl;
		}


	}
	Bill::Date finish(std::stoi(help[0]), std::stoi(help[1]), std::stoi(help[2]));

	if (finish < start)
	{
		cout << "Uneseni datumi nisu ispravni"<<endl; return;
	}
	system("cls");
	std::fstream file; file.open("Racuni za ispis.txt");
	if (!file.is_open())
		return;
	string current;

	cout << std::resetiosflags(std::ios::adjustfield);			
	cout << std::setiosflags(std::ios::left);					
	cout
		<< std::setw(15)
		<< "Datum"
		<< std::setw(20)
		<< "Kupac"
		<< std::setw(19)
		<< "Proizvod"
		<< std::setw(10)
		<< "Cijena"
		<< std::setw(10)
		<< "PDV(17%)"
		<< std::setw(10)
		<< "Kolicina"
		<< std::setw(10)
		<< "Ukupno"
		<< std::setw(15)
		<< "Ukupno sa PDV-om" << endl;
	cout << std::setfill('-') << std::setw(112) << " " << endl;

	while (std::getline(file, current))
	{
		std::vector<std::string> vec;
		Bill::split(current, '#', vec);
		Bill::Date date = vec[0];
		std::vector<Bill::Product> assistVector;
		
		Bill::Product temp  (vec[2], std::stod(vec[3]), std::stod(vec[4]), std::stod(vec[5]));
		assistVector.push_back(temp);
		for (int i = 1;i < stoi(vec[7]);i++)
		{
			vec.clear();
			std::getline(file, current);
			Bill::split(current, '#', vec);
			Bill::Product temp(vec[2], std::stod(vec[3]), std::stod(vec[4]), std::stod(vec[5]));
			assistVector.push_back(temp);
		}
		if (date > start && date < finish)
		{
			Bill assist(vec[1], date, assistVector);
			assist.writeBillToConsole();
		}
		
	}

	}

	void analiticar::Analiticar::billsProductOverview()
	{
		system("cls");
		std::fstream file; file.open("Racuni za ispis.txt");
		if (!file.is_open())
			return;
		string current, localProduct;
		bool quit = 0;
		while (!quit)
		{
			cout << "Unesite ime proizvoda:";
			std::getline(cin, localProduct);
			if (localProduct != " " && localProduct != "")
				quit = 1;
		}
		cout << std::resetiosflags(std::ios::adjustfield);
		cout << std::setiosflags(std::ios::left);
		cout																	//poubacivati ove headere u funkciju, jer su svaki put isti
			<< std::setw(15)
			<< "Datum"
			<< std::setw(20)
			<< "Kupac"
			<< std::setw(19)
			<< "Proizvod"
			<< std::setw(10)
			<< "Cijena"
			<< std::setw(10)
			<< "PDV(17%)"
			<< std::setw(10)
			<< "Kolicina"
			<< std::setw(10)
			<< "Ukupno"
			<< std::setw(15)
			<< "Ukupno sa PDV-om" << endl;
		cout << std::setfill('-') << std::setw(112) << " " << endl;

		while (std::getline(file, current))
		{
			std::vector<std::string> vec;
			Bill::split(current, '#', vec);
			vec[0][11] = ' '; Bill::Date date = vec[0];
			std::vector<Bill::Product> assistVector;

			Bill::Product temp(vec[2], std::stod(vec[3]), std::stod(vec[4]), std::stod(vec[5]));
			assistVector.push_back(temp);
			for (int i = 1;i < stoi(vec[7]);i++)
			{
				vec.clear();
				std::getline(file, current);
				Bill::split(current, '#', vec);
				Bill::Product temp(vec[2], std::stod(vec[3]), std::stod(vec[4]), std::stod(vec[5]));
				assistVector.push_back(temp);
			}
			for(int i =0;i<assistVector.size();i++)
				if (localProduct==assistVector[i].productKey)
				
			{
				Bill assist(vec[1], date, assistVector);
				assist.writeBillToConsole();
				break;
			}

		}


	}

	void analiticar::Analiticar::billsBuyerOverview()
	{
		
		string current, localBuyer;
		bool quit = 0;
		while (!quit)
		{
			cout << "Unesite ime kupca:";
			std::getline(cin, localBuyer);
			if (localBuyer != " " && localBuyer!= "")
				quit = 1;
		}
		system("cls");
		std::fstream file; file.open("Racuni za ispis.txt");
		if (!file.is_open())
			return;
		cout << std::resetiosflags(std::ios::adjustfield);
		cout << std::setiosflags(std::ios::left);
		cout
			<< std::setw(15)
			<< "Datum"
			<< std::setw(20)
			<< "Kupac"
			<< std::setw(19)
			<< "Proizvod"
			<< std::setw(10)
			<< "Cijena"
			<< std::setw(10)
			<< "PDV(17%)"
			<< std::setw(10)
			<< "Kolicina"
			<< std::setw(10)
			<< "Ukupno"
			<< std::setw(15)
			<< "Ukupno sa PDV-om" << endl;
		cout << std::setfill('-') << std::setw(112) << " " << endl;

		while (std::getline(file, current))
		{
			std::vector<std::string> vec;
			Bill::split(current, '#', vec);
			Bill::Date date = vec[0];
			std::vector<Bill::Product> assistVector;

			Bill::Product temp(vec[2], std::stod(vec[3]), std::stod(vec[4]), std::stod(vec[5]));
			assistVector.push_back(temp);
			for (int i = 1;i < stoi(vec[7]);i++)
			{
				vec.clear();
				std::getline(file, current);
				Bill::split(current, '#', vec);
				Bill::Product temp(vec[2], std::stod(vec[3]), std::stod(vec[4]), std::stod(vec[5]));
				assistVector.push_back(temp);
			}
			if (localBuyer == vec[1])

				{
					Bill assist(vec[1], date, assistVector);
					assist.writeBillToConsole();
					
				}

		}
	}





int analiticar::Analiticar::menu()
{
	Bill::billClassification();
	bool quit = 0;
	std::string choice;
	while (!quit)
	{
		cout << endl << "1.Pregled racuna po periodu izdavanja" << endl << "2.Pregled racuna po kupcu" << endl << "3.Pregled racuna po proizvodu" << endl <<  "4.Odjava korisnika" << endl << "5.Izlazak iz programa" << endl;
		cout << "Izaberite jednu od ponudjenih opcija: ";	getline(cin, choice);
		if (isdigit(choice[0]))
		{
			switch (std::stoi(choice))
			{
			case 1:
			{
				system("cls");
				this->billsDateOverview();
				cout << "Pritisnite enter da bi nastavili koristiti aplikaciju.."; getchar();
				system("cls");
			} break;
			case 2:
			{
				system("cls");
				this->billsBuyerOverview();
				cout << "Pritisnite enter da bi nastavili koristiti aplikaciju.."; getchar();
				system("cls");
			} break;
			case 3:
			{
				system("cls");
				this->billsProductOverview();
				cout << "Pritisnite enter da bi nastavili koristiti aplikaciju.."; getchar();
				system("cls");
			} break;
			case 4:
			{
				system("cls");
				return 0;
			} break;
			case 5:
			{   
				return 1;
			}	
			default:
			{
				system("cls");
				quit = 0;
			}

			}
		}
		else system("cls");
	}
}
