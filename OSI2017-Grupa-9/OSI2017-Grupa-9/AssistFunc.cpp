#include "AssistFunc.h"
#include "Administrator.h"
#include "Analiticar.h"

void writeInvalidLogin(string username, string p)
{
	std::fstream file;
	file.open(LogFile);
	if (!file.is_open())
		return;
	file.seekg(0, std::ios::end);
	file << username << " " << p << std::endl;
	file.close();
	return;

}

std::tuple<string, string, string, string, bool> logInCheck(std::fstream& file, string username, string p)
{
	file.clear();
	file.seekg(0, std::ios::beg);
	if (!file.is_open())
		return { "-1","-1","-1","-1",0 };
	string local_n, local_ln, local_p, local_username, type;

	while (file >> local_username >> local_n >> local_ln >> local_p >> type)
	{
		if (username == local_username && p == local_p)
		{
			system("cls");
			cout << " Uspjesno logovanje!" << endl << " Dobrodosli "  << local_n << endl;
			return { local_username,local_n,local_ln,local_p, std::stoi(type) };
		}

	}
	return { "-1","-1","-1","-1",0 };
}

std::tuple<string, string, string, string, bool> logIn()
{
	std::fstream file("test.txt");
	bool quit = false;
	string locUserName, locPw;
	std::tuple<string, string, string, string, bool> type;
	while (!quit)
	{
		cout << "Unesite korisnicko ime korisnika: ";
		getline(std::cin, locUserName);		

		cout << "Unesite pristupnu sifru korisnika: ";
		admin::readPIN_hidden(locPw);	

		if (admin::isPINokay(locPw) && (std::get<0>(type = logInCheck(file, locUserName, locPw)) != "-1"))	
		{
			quit = 1;
		}
		else
		{
			cout
				<< "Neuspjesno logovanje na sistem."
				<< endl
				<< "Unesite enter za ponovno unosenje podataka o korisniku";
		
			writeInvalidLogin(locUserName, locPw);

			getchar();
			system("cls");
		}
	}
	return type;
}

int runIt()

{

	bool quit = 0;
	while (!quit)
	{


		auto temp = logIn();
		if (std::get<4>(temp) == 1)
		{


			admin::Administrator current(temp);
			quit = current.menu();
		}
		else
		{
			analiticar::Analiticar current(temp);
			quit = current.menu();
		}
		system("cls");
	}
	return 0;
}

bool leapYear(int year)
{
	if (year % 4 == 0)
	{
		if (year % 100 == 0)
		{
			if (year % 400 == 0)
				return true;
			else
				return false;
		}
		else
			return true;
	}
	else
		return false;
}

bool isDateValid(int month, int day, int year)
{
	if (day < 1 || month < 1)
		return false;
	bool validation = true;
	switch (month)
	{
	case 2:
		if (leapYear(year))
		{
			if (day > 29)
				validation = false;
		}
			else
				if (day > 28)
					validation = false;
		break;
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		if (day > 31)
			validation = false;
		break;
	case 4: case 6: case 9: case 11:
		if (day > 30)
			validation = false;
		break;
	default:
		validation = false;
		break;
	}
	return validation;
}

