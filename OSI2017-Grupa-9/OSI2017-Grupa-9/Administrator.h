#pragma once
#include "usedLibs.h"
#include "User.h"


namespace admin
{
	class Administrator : user::User
	{
	private:

		User createNewUser() const;
		int getNumberOfUsers(std::fstream&) const;
		void showAvailableCurrencies(std::fstream&) const;
																				//protected:

		string getPIN() const;
		bool isPINokay(const string&) const;
    //	int findUser(std::fstream&) const;				metoda koja vraca poziciju unutar fajla na kojoj se nalazi trazeni korisnik.. ova metoda trazi da se unesu informacije o korisniku
	//  int findUser(std::tuple<...>&) const;			kao i metode za dodavanje, ovde su vec dostupne info o korisniku													
	public:

		Administrator();
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
		//setijsoptihjosith

	};
}
