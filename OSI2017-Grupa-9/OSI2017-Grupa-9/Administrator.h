#pragma once
#include "AssistFunc.h"
#include "User.h"


namespace admin
{
	class Administrator : public user::User
	{
	private:

		User createNewUser() const;
		int getNumberOfUsers(std::fstream&) const;
		void showAvailableCurrencies(std::fstream&) const;


		friend bool isPINokay(const string&);
		friend string getPIN();
		friend bool isUserNameOkay(const string,std::fstream&);
		friend string getUserName();
    //	int findUser(std::fstream&) const;				metoda koja vraca poziciju unutar fajla na kojoj se nalazi trazeni korisnik.. ova metoda trazi da se unesu informacije o korisniku
	//  int findUser(std::tuple<...>&) const;			kao i metode za dodavanje, ovde su vec dostupne info o korisniku													
	public:

		Administrator();
		Administrator(const std::tuple<string, string, string, string, bool>&);
		~Administrator();

		void userOverview(std::fstream&) const;
		void addNewUser(std::fstream&) const;		
	//	void addNewUser() const;														Unutar ove metode se vrsi upit o informacijama korisnika i onda se ubacuje u fajl kojem je putanja vec odredjena.
    //  void addnewUser(const std::tuple<string, string, string, bool>&) const			Ovde se dobijaju inform. o korisniku, i kao takav se odmah dodaje
		void deleteUser(std::fstream&) const;
    //  void deleteUser() const;														Na slican nacin su i ove 2 metode zamisljene, kao i gore navedene za dodavanje korisnika.
    //  void deleteUser(const std::tuple<string, string, string, bool>&) const;
		void changeCurrency(std::fstream&) const;		
		bool isLogInSuccesfull() const;
		int menu() const;
	};
}

