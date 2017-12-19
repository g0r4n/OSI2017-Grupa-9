#include"AssistFunc.h"
#include "Administrator.h"

void writeInvalidLogin(string n, string ln, string p) 
{
	std::fstream file;
	file.open(LogFile);
	if (!file.is_open())
		return;
	file.seekg(0, std::ios::end);
	file << n << " " <<  ln << " " << p<<std::endl;
	file.close();
	return;

}

int logInCheck(std::fstream& file, string n, string ln, string p) 
{
	file.clear();
	file.seekg(0, std::ios::beg);
	if (!file.is_open())
		return -1;
	string local_n, local_ln, local_p, type;

	while (file>>local_n>>local_ln>>local_p>>type)
	{
		if (n == local_n && ln == local_ln && p == local_p)
		{
			system("cls");
			cout << " Uspjesno logovanje!"<<"\n Dobrodosli "<<local_n;
			return std::stoi(type);
		}
		
	}
	return -1;
 }

std::tuple<string,string,string,bool> logIn()
{
	std::fstream file(UserDataFile);
	bool quit = false;
	string loc_n,loc_ln,loc_pw;
	int type;
	while (!quit)
	{
		// cout<<"Unesite ime prezime i PIN korisnika; cin >> loc_n >> loc_ln >> loc_pw;
		cout << "Unesite ime korisnika: ";
		getline(std::cin, loc_n);

		cout << "Unesite prezime korisnika: ";
		getline(std::cin, loc_ln);

		cout << "Unesite pristupnu sifru korisnika: ";  
		getline(std::cin, loc_pw);

		if (loc_pw.length() == 4 && ((type = logInCheck(file, loc_n, loc_ln, loc_pw))!=-1))
		 {
				 quit = 1;
		 }
		else
		{
			cout << "Neuspjesno logovanje na sistem. Pritisnite enter za ponovno unosenje podataka o korisniku, ili Esc za izlazak iz programa. \n"; //Skontati kako detektovati Esc
			writeInvalidLogin(loc_n, loc_ln, loc_pw);
			/*
			while ((GetKeyState(VK_ESCAPE) || GetKeyState(VK_RETURN)))
			{
				

			}*/
			getchar();
			system("cls");
		}
	}
	return { loc_n,loc_ln,loc_pw,type };
}