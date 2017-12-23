#include "Administrator.h"
#include <locale>
using namespace admin;
using namespace user;


User admin::Administrator::createNewUser() const
{
	string username,name, surename, PIN; bool userGroup;
	cout << "Korisnicko ime(username): "; getline(cin, username);
	cout << "Ime: "; getline(cin, name);
	cout << "Prezime: "; getline(cin, surename);
	PIN = getPIN();
	cout << "Korisnica grupa(0,1): "; cin >> userGroup;			//exception ako korisnik unese pogresno
	cin.ignore();												//ignorise '\n' || endl kada se unese izbor za korisnicku grupu(cin problem)
	return User({username,name,surename,PIN,userGroup});
}

int admin::Administrator::getNumberOfUsers(std::fstream& fileWithUsers) const
{
	if (fileWithUsers.is_open())		//exception
	{
		string line;
		int numberOfLines = 0;
		while (getline(fileWithUsers, line))
			numberOfLines++;
		fileWithUsers.seekg(0);
		return numberOfLines;
	}
}

void admin::Administrator::showAvailableCurrencies(std::fstream& fileWithCurrencies) const
{
	if (fileWithCurrencies.is_open())		//exception
	{
		fileWithCurrencies.seekg(0);
		cout << "Dostupne valute su: " << endl;
		string line;
		while (fileWithCurrencies >> line)
			cout << line << endl;
	}
}

bool admin::isPINokay(const string& PIN)
{
	if (PIN.length() != 4)
		return false;
	for (char c : PIN)				// provjera da li su svi karakteri PIN-a brojevi
		if (!(c >= '0' && c <= '9'))
			return false;
	return true;
}

string admin::getPIN()
{
	string PIN;
	do
	{
		cout << "PIN: ";
		getline(cin, PIN);
		if (!isPINokay(PIN))
			cout << "Pogresan unos!" << endl;
	} while (!isPINokay(PIN));
	return PIN;
}

bool admin::isUserNameOkay(const string username,std::fstream& fileWithUsers)
{
	if (fileWithUsers.is_open())
	{
		user::User u;
		while (fileWithUsers >> u)
			if (u.getUserName() == username)
				return false;
	}
	return true;
}

string admin::getUserName()
{
	std::fstream fileWithUsers(UserDataFile, std::ios::in);
	if (fileWithUsers.is_open())//exception
	{
		string username;
		do
		{
			cout << "Unesite korisnicko ime korisnika: "; getline(cin, username);
		} while (!isUserNameOkay(username, fileWithUsers));
		return username;
	}
}



admin::Administrator::Administrator(){}

admin::Administrator::Administrator(const std::tuple<string, string, string, string, bool>& userInfo){}

admin::Administrator::~Administrator(){}

void admin::Administrator::userOverview(std::fstream& fileWithUsers) const
{
	if (fileWithUsers.is_open())										//excpetion!!!
	{
		if(stati_cast<int>(fileWithUsers.tellg()) != 0)
			fileWithUser.seekg(0);
		//fileWithUsers(fileWithUsers.path(), std::ios::in);	ako fajl nije otvoren, otvoriti ga... ustanoviti gdje ce se fajl nalaziti i upisati ga umjesto kvazifunkcije path
		user::User u;
		cout << "Lista svih korisnika: " << endl;
		while (fileWithUsers >> u)
			cout << u << endl;
	}
}

void admin::Administrator::addNewUser(std::fstream& fileWithUsers) const
{
	if (fileWithUsers.is_open())			//exception			// provjera u kom "modu" je otvorena dat
	{
		fileWithUsers.seekg(0);				// pozicionira indikator unutar fajla na pocetak tog fajla*/
		User u = createNewUser();
		/*User x;

		for (int startPosition = fileWithUsers.tellg(), newPosition; fileWithUsers >> x && h; startPosition = fileWithUsers.tellg())
		{
			newPosition = fileWithUsers.tellg();
			if (u < x)
			{
				fileWithUsers.seekg(startPosition, std::ios::beg);
				fileWithUsers << endl;
				fileWithUsers.seekg(startPosition, std::ios::beg);
				fileWithUsers << u;
				h = false;
			}
			else if (u > x)
			{
				fileWithUsers.seekg(newPosition, std::ios::beg);
				fileWithUsers << endl;
				fileWithUsers.seekg(newPosition, std::ios::beg);
				fileWithUsers << u;
				h = false;
			}
		}
		*/

			std::vector<User> arr;
			for (User x; fileWithUsers >> x; arr.push_back(x));
			fileWithUsers.close();
			arr.push_back(u);
			std::sort(arr.begin(), arr.end(), [](User a, User b) {		return a < b;	});
			fileWithUsers.open(UserDataFile, std::ios::out | std::ios::trunc);	//brise sve iz datoteke i onda upisuje sortirane u tu istu
			for (User& u : arr)
				fileWithUsers << u << endl;		
	}
}

void admin::Administrator::deleteUser(std::fstream& fileWithUsers) const
{
	if (fileWithUsers.is_open())
	{
		//fileWithUsers.clear();	?
		fileWithUsers.seekg(0);			//rewind
		string name, surename;
		cout << "Unesite ime i prezime korisnika kojeg zelite ukloniti: "; cin >> name >> surename;
		std::vector<User> arr;
		for (User x; fileWithUsers >> x; arr.push_back(x));
		fileWithUsers.close();

		std::sort(arr.begin(), arr.end(), [](User a, User b) {return a < b;});
		int position = -1;
		for (int i = 0; i < arr.size() && position == -1; i++)			
			if (arr[i] == User({ "",name,surename,"",false }))
				position = i;
		arr.erase(arr.begin() + position);


		fileWithUsers.open(UserDataFile, std::ios::out | std::ios::trunc);	//brise sve iz datoteke i onda upisuje sortirane u tu istu
		for (User& u : arr)
			fileWithUsers << u << endl;
	}
}

void admin::Administrator::changeCurrency(std::fstream& fileWithCurrencies) const
{
	if (fileWithCurrencies.is_open())			// dovrsiti sa tramom 		gdje se cuvaju podaci o valutama?
	{
		string currency;
		showAvailableCurrencies(fileWithCurrencies);
		cout << "Izaberite valutu: "; getline(cin, currency);
	}
}

int admin::Administrator::menu() const
{
	bool quit = 0;
	std::string choice;
	while (!quit)
	{
		cout << endl << "1.Pregled svih korisnika" << endl << "2.Dodavanje novog korisnika" << endl << "3.Brisanje postojeceg korisnika" << endl << "4.Promjena valute" << endl << "5.Odjava korisnika" << endl << "6.Izlazak iz programa" << endl;
		std::getline(cin, choice);
		if (isdigit(choice[0]))
		{
			switch (std::stoi(choice))
			{
			case 1:
			{
				system("cls");
				std::fstream file; file.open(UserDataFile);
				this->userOverview(file);
				file.close();
				system("cls");
			} break;
			case 2:
			{
				system("cls");
				std::fstream file; file.open(UserDataFile);
				this->addNewUser(file);
				file.close();
				system("cls");
			} break;
			case 3:
			{
				system("cls");
				std::fstream file; file.open(UserDataFile);
				this->deleteUser(file);
				file.close();
				system("cls");
			} break;
			case 4:
			{
				system("cls");
				std::fstream file; file.open(ConfigFile);
				this->changeCurrency(file);
				file.close();
				system("cls");
			} break;
			case 5:
			{   system("cls");
			return 0;
			}
			case 6:
				exit(0);
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

