#include "Administrator.h"
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
	string line;
	int numberOfLines = 0;
	while (getline(fileWithUsers, line))
		numberOfLines++;
	fileWithUsers.seekg(0);
	return numberOfLines;
}

void admin::Administrator::showAvailableCurrencies(std::fstream& fileWithCurrencies) const
{
	if (fileWithCurrencies.is_open())		//exception
	{
		cout << "Dostupne valute su: " << endl;
		string line;
		while (fileWithCurrencies >> line)
			cout << line << endl;
	}
}

string admin::Administrator::getPIN() const
{
	string PIN;
	do
	{
		cout << "PIN: ";
		getline(cin, PIN);
		if (!isPINokay(PIN))
			cout << "Pogresan unos! PIN sadrzi 4 broja." << endl;
	} while (!isPINokay(PIN));
	return PIN;
}

bool admin::Administrator::isPINokay(const string& PIN) const
{
	if (PIN.length() != 4)
		return false;
	for (char c : PIN)				// provjera da li su svi karakteri PIN-a brojevi
		if (!(c >= '0' && c <= '9'))
			return false;
	return true;
}

admin::Administrator::Administrator(){}

admin::Administrator::~Administrator(){}

void admin::Administrator::userOverview(std::fstream& fileWithUsers) const
{
	if (fileWithUsers.is_open())										//excpetion!!!
	{
		//fileWithUsers(fileWithUsers.path(), std::ios::in);	ako fajl nije otvoren, otvoriti ga... ustanoviti gdje ce se fajl nalaziti i upisati ga umjesto kvazifunkcije path
		string username, name, surename, PIN;
		bool userGroup;
		cout << "Lista svih korisnika: " << endl;
		while (fileWithUsers >> username >> name >> surename >> PIN >> userGroup)
			cout << username << name << " " << surename << " " << PIN << " " << userGroup << endl;
	}
}

void admin::Administrator::addNewUser(std::fstream& fileWithUsers) const
{
	if (fileWithUsers.is_open())			//exception			// provjera u kom "modu" je otvorena dat
	{
		/*bool h = true;
		fileWithUsers.seekg(0);				// pozicionira indikator unutar fajla na pocetak tog fajla*/
		fileWithUsers.seekg(0);
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
		//fileWithUsers.clear();
		fileWithUsers.seekg(0);			//rewind
		string name, surename;
		cout << "Unesite ime i prezime korisnika kojeg zelite ukloniti: "; cin >> name >> surename;
		std::vector<User> arr;
		for (User x; fileWithUsers >> x; arr.push_back(x));
		fileWithUsers.close();

		std::sort(arr.begin(), arr.end(), [](User a, User b) {		return a < b;	});
		int position = -1;
		for (int i = 0; i < arr.size() && position == -1; i++)			//EXCEPTION
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
	if (fileWithCurrencies.is_open())			// dovrsiti sa tramom 
	{
		string currency;
		showAvailableCurrencies(fileWithCurrencies);
		cout << "Izaberite valutu: "; getline(cin, currency);
	}
}

