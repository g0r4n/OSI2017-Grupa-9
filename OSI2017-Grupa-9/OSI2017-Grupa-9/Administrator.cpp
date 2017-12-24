#include "Administrator.h"
#include <locale>
using namespace admin;
using namespace user;


User admin::Administrator::createNewUser() const
{
	cout << "Unesite informacije o novom korisniku: " << endl;
	string username,name, surename, PIN; bool userGroup;
	string userGroup_temp;

	username = getUserName();		//odraditi provjeru za "space" i sankcionisati je
	cout << "Ime: "; getline(cin, name);
	cout << "Prezime: "; getline(cin, surename);
	PIN = getPIN();
	userGroup = getUserGroup();

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

string admin::Administrator::getPIN() const 
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

bool admin::Administrator::isUserNameOkay(const string username, std::fstream& fileWithUsers) const 
{
	if (!fileWithUsers.is_open())
		fileWithUsers.open("test.txt", std::ios::out | std::ios::in);
	fileWithUsers.clear();
	fileWithUsers.seekg(0);
	user::User u;
	while (fileWithUsers >> u)
		if (u.getUserName() == username)
		{
			fileWithUsers.close();
			return false;
		}
	fileWithUsers.close();
	return true;
}

string admin::Administrator::getUserName() const
{
	std::fstream fileWithUsers("test.txt", std::ios::out | std::ios::in);
	string username;

	cout << "Korisnicko ime: ";
	getline(cin, username);
	while (!isUserNameOkay(username, fileWithUsers))
	{
		cout << "Korisnicko ime je zauzeto. Unesite novo: ";
		getline(cin, username);
	}
	return username;
}

bool admin::Administrator::isUserGroupOkay(const string userGroup) const
{
	int x = std::stoi(userGroup);
	if (x == 0 || x == 1)
		return true;
	return false;
}

bool admin::Administrator::getUserGroup() const
{
	string ug_temp; bool userGroup;
	cout << "Korisnica grupa(0- Analiticar ,1- Administrator): "; getline(cin, ug_temp);
	while (!isUserGroupOkay(ug_temp))
	{
		cout << "Pogresan unos! Pokusajte ponovo" << endl;
		cout << "Korisnica grupa(0- Analiticar ,1- Administrator): "; getline(cin, ug_temp);
	}
	userGroup = static_cast<bool>(std::stoi(ug_temp));
	return userGroup;
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

admin::Administrator::Administrator(){}

admin::Administrator::Administrator(const std::tuple<string, string, string, string, bool>& userInfo) : user::User(userInfo) {}

admin::Administrator::~Administrator(){}

void admin::Administrator::userOverview(std::fstream& fileWithUsers) const
{
	if (!fileWithUsers.is_open())
		fileWithUsers.open("test.txt", std::ios::in);
	if (static_cast<int>(fileWithUsers.tellg()) != 0)
		fileWithUsers.seekg(0);
	user::User u;

	cout << std::resetiosflags(std::ios::adjustfield);			// resetovanje 
	cout << std::setiosflags(std::ios::left);					// poravnanje u lijevo

	cout << "Lista svih korisnika: " << endl;


	for (int i = 0; i < 75; i++) cout << "=";
	cout << endl;

	cout
		<< std::setw(16)
		<< "Korisnicko ime"
		<< " "
		<< std::setw(16)
		<< "Ime"
		<< " "
		<< std::setw(16)
		<< "Prezime"
		<< " "
		<< std::setw(5)
		<< "PIN"
		<< " "
		//<<std::setw(4)
		<< "Korisnicka grupa" << endl;

	for (int i = 0; i < 75; i++) cout << "="; cout << endl;

	while (fileWithUsers >> u)
		cout << u << endl;

	for (int i = 0; i < 75; i++) cout << "=";
	cout << endl;
}

void admin::Administrator::addNewUser(std::fstream& fileWithUsers) const
{
	if (!fileWithUsers.is_open())
		fileWithUsers.open("test.txt", std::ios::out | std::ios::in);
	fileWithUsers.clear();
	fileWithUsers.seekg(0);												// pozicionira indikator unutar fajla na pocetak tog fajla

	User u = createNewUser();
	std::vector<User> arr;
	for (User pom; fileWithUsers >> pom; arr.push_back(pom));

	arr.push_back(u);
	std::sort(arr.begin(), arr.end());

	fileWithUsers.close();
	fileWithUsers.open("test.txt", std::ios::out | std::ios::trunc);	//brise sve iz datoteke i onda upisuje sortirane u tu istu
	for (User &u : arr)
		fileWithUsers << u << endl;
	fileWithUsers.close();

}

void admin::Administrator::deleteUser(std::fstream& fileWithUsers) const
{
	if (!fileWithUsers.is_open())
		fileWithUsers.open("test.txt", std::ios::out | std::ios::in);
	fileWithUsers.clear();
	fileWithUsers.seekg(0);								//rewind


	string username;
	cout << "Unesite KORISNICKO ime(username) korisnika kojeg zelite obrisati: "; getline(cin, username);	//namjestiti da baci exception ako je admin upisao svoje ime za brisanje
	User toErase({ username,"", "", "", false });

	if (toErase == *this)
	{
		cout
			<< "Administrator ne moze ukloniti samog sebe sa sistema. "
			<< endl
			<< "Za izlaz iz aplikacije pritisnite bilo sta." << endl;
		cout << "Pritisnite bilo sta za prekid rada programa";
		getchar();

	}

	else
	{
		std::vector<User> arr;
		/*while (static_cast<int>(fileWithUsers.tellg()) != EOF)
		{
			User pom;
			fileWithUsers >> pom;
			arr.push_back(pom);
		}*/


		for (User pom; fileWithUsers >> pom; arr.push_back(pom));
		fileWithUsers.close();

		std::sort(arr.begin(), arr.end());					//sortira rastuce po default-u

		auto exist = std::find(arr.begin(), arr.end(), toErase);
		/*
			Ako postoji trazeni element unutar vektora(tacnije unutar fajla koji je ucitan u vektor),
			tada ce exist biti iterator na taj element.
			Ako ne postoji, exist ce biti pokazivac na element POSLIJE POSLJEDNJEG unutar vektora(klasa std::vector je tako
			realizovana da je njen "end" element poslije posljednjeg.
		*/
		if (exist != std::end(arr))
		{
			arr.erase(std::remove(arr.begin(), arr.end(), toErase), arr.end());
			cout << "Korisnik " << username << " uspjesno obrisan." << endl;
		}
		else
			cout << "Korisnik kojeg ste unijeli na postoji!" << endl;


		fileWithUsers.open("test.txt", std::ios::out | std::ios::trunc);	//brise sve iz datoteke i onda upisuje sortirane u tu istu
		for (User& u : arr)
			fileWithUsers << u << endl;
	}
	fileWithUsers.close();
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
		cout << "Izaberite jednu od ponudjenih opcija: ";	getline(cin, choice);
		if (isdigit(choice[0]))
		{
			switch (std::stoi(choice))
			{
			case 1:
			{
				system("cls");
				std::fstream file; file.open("test.txt");
				this->userOverview(file);
				file.close();
				cout << "Pritisnite bilo sta da nastavite koristiti aplikaciju: "; getchar();
				system("cls");
			} break;
			case 2:
			{
				system("cls");
				std::fstream file; file.open("test.txt");
				this->addNewUser(file);
				file.close();				
				cout << "Pritisnite bilo sta da nastavite koristiti aplikaciju: "; getchar();
				system("cls");
			} break;
			case 3:
			{
				system("cls");
				std::fstream file; file.open("test.txt");
				this->deleteUser(file);
				file.close();
				cout << "Pritisnite bilo sta da nastavite koristiti aplikaciju: "; getchar();
				system("cls");
			} break;
			case 4:
			{
				system("cls");
				std::fstream file; file.open(ConfigFile);
				this->changeCurrency(file);
				file.close();
				cout << "Pritisnite bilo sta da nastavite koristiti aplikaciju: "; getchar();
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

