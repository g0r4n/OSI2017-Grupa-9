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
		void showAvailableCurrencies() const;


		friend void readPIN_hidden(string&);
		friend bool isPINokay(const string&);
		friend bool isCurrencyOkay(const string&);
		friend string getCurrentCurrency();


		string getPIN() const;
		bool isUserNameOkay(const string,std::fstream&) const;
		string getUserName() const;
		bool isUserGroupOkay(const string) const;
		bool getUserGroup() const;
    												
	public:

		Administrator();
		Administrator(const std::tuple<string, string, string, string, bool>&);
		~Administrator();
		void userOverview(std::fstream&) const;
		void addNewUser(std::fstream&) const;
		void editUser(std::fstream&) const;
		void deleteUser(std::fstream&) const;
 		void changeCurrency(std::fstream&) const;		
		void checkFailedLogins() const;
		int menu() const;
		
	};
}

