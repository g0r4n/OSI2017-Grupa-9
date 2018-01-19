#include "Administrator.h"
using namespace admin;
using namespace user;

User admin::Administrator::createNewUser() const
{
	cout << "Unesite informacije o novom korisniku: " << endl;
	string username, name, surename, PIN; bool userGroup;
	string userGroup_temp;

	username = getUserName();		//odraditi provjeru za "space" i sankcionisati je

	do
	{
		cout << "Ime: "; getline(cin, name);
	} while (name.length() < 1 || name.at(0) == ' ');				//do while petlja postoji zbog mogucnosti da se napravi prazan string ako se samo pritsne enter(\n, endl)
	do
	{
		cout << "Prezime: "; getline(cin, surename);
	} while (surename.length() < 1 || surename.at(0) == ' ');

	PIN = getPIN();
	userGroup = getUserGroup();

	return User({username,name,surename,PIN,userGroup});
}

int admin::Administrator::getNumberOfUsers(std::fstream& fileWithUsers) const
{
	if (!fileWithUsers.is_open())
		fileWithUsers.open(UserDataFile, std::ios::in);
	string line;
	int numberOfLines = 0;
	while (getline(fileWithUsers, line))
		numberOfLines++;
	fileWithUsers.seekg(0);
	return numberOfLines;
}

void admin::Administrator::showAvailableCurrencies() const
{
	cout
		<< "Dostupne valute su: "
		<< endl
		<< "KM (Konvertibilna marka)"
		<< endl
		<< "$ (Americki dolar)"
		<< endl
		<< "e (EURO)"
		<< endl;
	
}


string admin::Administrator::getPIN() const 
{
	string PIN, validation_PIN;
	bool isNotCorrect = true;
	do
	{
		cout << "PIN: ";
		readPIN_hidden(PIN);
		if (!isPINokay(PIN))
			cout << "Pogresan unos! Unesite ponovo!" << endl;
		else
		{
			cout << "Potvrdite PIN: ";
			readPIN_hidden(validation_PIN);
			if (isPINokay(validation_PIN) && PIN == validation_PIN)
				isNotCorrect = false;
			else
				cout << "Pogresan unos ili se PIN-ovi ne poklapaju!" << endl;
		}
	} while (isNotCorrect);


	return PIN;
}

bool admin::Administrator::isUserNameOkay(const string username, std::fstream& fileWithUsers) const 
{
	if (!fileWithUsers.is_open())
		fileWithUsers.open(UserDataFile, std::ios::out | std::ios::in);
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
	std::fstream fileWithUsers(UserDataFile, std::ios::out | std::ios::in);
	string username;

	do
	{
		cout << "Korisnicko ime: ";
		getline(cin, username);
	} while (username.length() < 1 || username.at(0) == ' ');					//korsitenej do while petlje je objasnjeno u funkciji createNewUser()
	while (!isUserNameOkay(username, fileWithUsers))
	{
		cout << "Korisnicko ime je zauzeto. Unesite novo: ";
		getline(cin, username);
	}
	return username;
}


bool admin::Administrator::isUserGroupOkay(const string userGroup) const
{
	if (userGroup.length() > 1) return false;

	/*try-catch blok ce se izvrsiti samo ako je dobijeni string ima samo jedan karakter*/

	try
	{
		int x = std::stoi(userGroup);			
		if (x == 0 || x == 1)
			return true;
		return false;
	}
	catch (std::invalid_argument& ex)	// u slucaju da se upise samo string(ili prazan string), std::stoi baca exception invalid_argument
	{
		return false;
	}
}

bool admin::Administrator::getUserGroup() const
{
	string ug_temp; bool userGroup;
	cout << "Korisnicka grupa(0 - Analiticar, 1 - Administrator): "; getline(cin, ug_temp);
	while (!isUserGroupOkay(ug_temp))
	{
		cout << "Pogresan unos! Pokusajte ponovo" << endl;
		cout << "Korisnicka grupa(0 - Analiticar, 1 - Administrator): "; getline(cin, ug_temp);
	}
	userGroup = static_cast<bool>(std::stoi(ug_temp));
	return userGroup;
}

void admin::readPIN_hidden(string& str)
{
	str.clear();
	bool end = false;
	char x;
	do
	{
		x = _getch();
		switch (x)
		{
		case 0:
			cin.ignore();
			break;
		case 8:				//8- ASCII vrijednost za Backspace
			if (str.length() > 0)
			{
				str.erase(str.end() - 1);		//obrise zadnji karakter u stringu
				cout << x << ' ' << x;			//bacspace se vrati karakter unazad, prepise razmak preko njega, i opet se vrati karakter(preko space) unazad;
			}
			break;
		case 13:				//13- decimalna vrijednost za ENTER(new line)
			end = true;
			cout << endl;
			break;
		default:
			str += x;
			cout << '*';
			break;
		}
	} while (!end);
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

bool admin::isCurrencyOkay(const string &currency)
{
	if (currency == "KM" || currency == "$" || currency == "e")
		return true;
	return false;
}

string admin::getCurrentCurrency()
{
	std::fstream fileWithCurrencies(CurrenciesFile, std::ios::in);
	string currency;
	fileWithCurrencies >> currency;
	return currency;
}

admin::Administrator::Administrator(){}

admin::Administrator::Administrator(const std::tuple<string, string, string, string, bool>& userInfo) : user::User(userInfo) {}

admin::Administrator::~Administrator(){}

void admin::Administrator::userOverview(std::fstream& fileWithUsers) const
{
	if (!fileWithUsers.is_open())
		fileWithUsers.open(UserDataFile, std::ios::in);
	if (static_cast<int>(fileWithUsers.tellg()) != 0)
		fileWithUsers.seekg(0);
	user::User u;

	cout << std::resetiosflags(std::ios::adjustfield);			// resetovanje 
	cout << std::setiosflags(std::ios::left);					// poravnanje u lijevo

	cout << "Lista svih korisnika: " << endl;


	for (int i = 0; i < 75; i++) cout << "=";
	cout << endl;

	cout << std::setfill(' ')
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
		fileWithUsers.open(UserDataFile, std::ios::out | std::ios::in);
	fileWithUsers.clear();
	fileWithUsers.seekg(0);												// pozicionira indikator unutar fajla na pocetak tog fajla

	User u = createNewUser();
	std::vector<User> arr;
	for (User pom; fileWithUsers >> pom; arr.push_back(pom));

	arr.push_back(u);
	std::sort(arr.begin(), arr.end());

	fileWithUsers.close();
	fileWithUsers.open(UserDataFile, std::ios::out | std::ios::trunc);	//brise sve iz datoteke i onda upisuje sortirane u tu istu
	for (User &u : arr)
		fileWithUsers << u << endl;
	fileWithUsers.close();

}

void admin::Administrator::editUser(std::fstream& fileWithUsers) const
{
	string username_temp;
	do
	{
		cout << "Unesite korisnicko ime(username) korisnika kom zelite promijeniti informacije: ";
		getline(cin, username_temp);
	} while (username_temp.length() < 1 || username_temp.at(0) == ' ');

	std::vector<User> arr;
	for (User pom; fileWithUsers >> pom; arr.push_back(pom));
	User toEdit({ username_temp, "","","",false });
	auto exist = std::find(arr.begin(), arr.end(), toEdit);
	/*
	Ako postoji trazeni element unutar vektora(tacnije unutar fajla koji je ucitan u vektor),
	tada ce exist biti iterator na taj element.
	Ako ne postoji, exist ce biti pokazivac na element POSLIJE POSLJEDNJEG unutar vektora(klasa std::vector je tako
	realizovana da je njen "end" element poslije posljednjeg.
	*/

	if (exist != arr.end())
	{
		string choice;
		string function;
		do
		{

			cout
				<< endl << endl
				<< '\t' << "1. Korisnicko ime(username)" << endl
				<< '\t' << "2. Ime" << endl
				<< '\t' << "3. Prezime" << endl
				<< '\t' << "4. PIN" << endl
				<< '\t' << "5. Korisnicku grupu" << endl
				<< '\t' << "6. Sve" << endl << endl << endl;

			do
			{
				cout << "Izaberite koju/e informaciju/e o korisniku zelite promijeniti(unesite broj, npr. 2 za ime): " ;
				getline(cin, function);
				cout << endl;
			} while (function.length() > 1 || (std::stoi(function) > 6 || std::stoi(function) < 1) );


			switch (std::stoi(function))
			{

			case 1:
			{
				exist->setUserName(getUserName());
				break;
			}
			case 2:
			{
				string name_temp;
				do
				{
					cout << "Unesite novo ime za datog korisnika: ";
					getline(cin, name_temp);
				} while (name_temp.length() < 1 || name_temp.at(0) == ' ');
				exist->setName(name_temp);
				break;
			}
			case 3:
			{
				string surename_temp;
				do
				{
					cout << "Unesite novo prezime za datog korisnika: ";
					getline(cin, surename_temp);
				} while (surename_temp.length() < 1 || surename_temp.at(0) == ' ');
				exist->setSureName(surename_temp);
				break;
			}
			case 4:
			{
				cout << "Unesite novi ";	// funkcija getPIN ce ispisati: "PIN: " 
				exist->setPIN(getPIN());
				break;
			}
			case 5:
			{
				bool userGroup_temp;
				cout << "Unesite novu korisnicku grupu" << endl;
				exist->setUserGroup(getUserGroup());
				break;
			}
			case 6:
			{
				*exist = createNewUser();
				choice = "Q";	//ako je korisnik u potpunosti promijenjen, nema smisla opet raditi neku pojedinacnu promjenu na njemu
				break;
			}
			default:
			{
				cout << "Pogresan unos!" << endl;
				break;
			}

			}

			cout 
				<< endl
				<< endl
				<< "Ako zelite prekinuti koristenje ove funkcije, unesite Q." 
				<< endl
				<< "Ako zelite nastaviti, Unesite bilo sta...";

			getline(cin, choice);

		} while (choice != "Q");

		fileWithUsers.close();
		fileWithUsers.open(UserDataFile, std::ios::out | std::ios::trunc);	//brise sve iz datoteke i onda upisuje sortirane u tu istu
		for (User &x : arr)
			fileWithUsers << x << endl;
		fileWithUsers.close();
	}
	else
		cout << "Korisnik sa tim korisnickim imenom ne postoji!" << endl;
	
}

void admin::Administrator::deleteUser(std::fstream& fileWithUsers) const
{
	if (!fileWithUsers.is_open())
		fileWithUsers.open(UserDataFile, std::ios::out | std::ios::in);
	fileWithUsers.clear();
	fileWithUsers.seekg(0);								//rewind


	string username;
	cout << "Unesite KORISNICKO ime(username) korisnika kojeg zelite obrisati: "; getline(cin, username);	//namjestiti da baci exception ako je admin upisao svoje ime za brisanje
	User toErase({ username,"", "", "", false });

	if (toErase == *this)
	{
		cout
			<< "Administrator ne moze ukloniti samog sebe sa sistema." << endl;
	}

	else
	{
		std::vector<User> arr;
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


		fileWithUsers.open(UserDataFile, std::ios::out | std::ios::trunc);	//brise sve iz datoteke i onda upisuje sortirane u tu istu
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
		showAvailableCurrencies();
		cout << "Izaberite valutu: "; getline(cin, currency);
		while (!isCurrencyOkay(currency))
		{
			cout << "Valuta ne postoji! Unesite ponovo: ";
			getline(cin, currency);
		}
		fileWithCurrencies.close();
		fileWithCurrencies.open(CurrenciesFile, std::ios::out | std::ios::trunc);	//otvori file i obrise sve iz njega
		cout << "Valuta uspjesno promijenjena u: " << currency << endl;
		fileWithCurrencies << currency;
	}
}

void admin::Administrator::checkFailedLogins() const
{
	std::fstream fileWithFailedLogins(LogFile, std::ios::in);
	string line;
	
	cout << "Spisak neuspjesnih prijava na sistem: " << endl;
	cout << std::resetiosflags(std::ios::adjustfield);			// resetovanje 
	cout << std::setiosflags(std::ios::left);					// poravnanje u lijevo

	cout << std::setfill(' ') << std::setw(112) << " " << endl;

	while (getline(fileWithFailedLogins, line))
		cout << line << endl;

	cout << std::setfill(' ') << std::setw(112) << " " << endl;
	cout << std::setfill(' ');

}

int admin::Administrator::menu() const
{
	bool quit = 0;
	string choice;
	while (!quit)
	{
		cout 
			<< endl 
			<< "1.Pregled svih korisnika" << endl 
			<< "2.Dodavanje novog korisnika" << endl 
			<< "3.Promjena informacija o postojecem korisniku" << endl
			<< "4.Brisanje postojeceg korisnika" << endl 
			<< "5.Promjena valute" << endl 
			<< "6.Pregled neuspjesnih prijava na sistem" << endl
			<< "7.Odjava korisnika" << endl 
			<< "8.Izlazak iz programa" << endl;

		cout << "Izaberite jednu od ponudjenih opcija: ";	getline(cin, choice);
		if (choice.length() == 1 && isdigit(choice[0]))
		{
			switch (std::stoi(choice))
			{
			case 1:
			{
				system("cls");
				std::fstream file; file.open(UserDataFile);
				this->userOverview(file);
				file.close();
				cout << "Unesite bilo sta da nastavite koristiti aplikaciju..."; getchar();
				system("cls");
			} break;
			case 2:
			{
				system("cls");
				std::fstream file; file.open(UserDataFile);
				this->addNewUser(file);
				file.close();
				cout << "Unesite bilo sta da nastavite koristiti aplikaciju: "; getchar();
				system("cls");
			} break;
			case 3:
			{
				system("cls");
				std::fstream file; file.open(UserDataFile);
				this->editUser(file);
				file.close();
				cout << "Unesite bilo sta da nastavite koristiti aplikaciju: "; getchar();
				system("cls");
			} break;
			case 4:
			{
				system("cls");
				std::fstream file; file.open(UserDataFile);
				this->deleteUser(file);
				file.close();
				cout << "Unesite bilo sta da nastavite koristiti aplikaciju: "; getchar();
				system("cls");
			} break;
			case 5:
			{
				system("cls");
				std::fstream file; file.open(CurrenciesFile);
				this->changeCurrency(file);
				file.close();
				cout << "Unesite bilo sta da nastavite koristiti aplikaciju: "; getchar();
				system("cls");
			} break;
			case 6:
			{
				system("cls");
				this->checkFailedLogins();
				cout << "Unesite bilo sta da nastavite koristiti aplikaciju: "; getchar();
				system("cls");
			} break;
			case 7:
			{   system("cls");
			return 0;
			}
			case 8:
				return 1;
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
		
	




