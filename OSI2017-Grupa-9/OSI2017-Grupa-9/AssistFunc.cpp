#include"AssistFunc.h"
void writeInvalidLogin(std::string n, std::string ln, std::string p) 
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
int logInCheck(std::fstream& file, std::string n, std::string ln, std::string p) 
{
	file.clear();
	file.seekg(0, std::ios::beg);
	if (!file.is_open())
		return 0;
	std::string local_n, local_ln, local_p, type;

	while (file>>local_n>>local_ln>>local_p>>type)
	{
		if (n == local_n && ln == local_ln && p == local_p)
		{
			system("cls");
			std::cout << " Uspjesno logovanje!"<<"\n Dobrodosli "<<local_n;
			return std::stoi(type);
		}
		
	}
	return 0;
 }

std::tuple<std::string,std::string,std::string,int> logIn()
{
	std::fstream file(UserDataFile);
	bool quit = 0;
	std::string loc_n,loc_ln,loc_pw;
	int type;
	while (!quit)
	{
		std::cout << "Unesite ime korisnika: ";
		std::getline(std::cin, loc_n);

		std::cout << "\nUnesite prezime korisnika: ";
		std::getline(std::cin, loc_ln);

		std::cout << "\nUnesite pristupnu sifru korisnika: ";  
		std::getline(std::cin, loc_pw);

		if (loc_pw.length() == 4 && (type = logInCheck(file, loc_n, loc_ln, loc_pw)))
		 {
				 quit = 1;
		 }
		else
		{
			std::cout << "Neuspjesno logovanje na sistem. Pritisnite enter za ponovno unosenje podataka o korisniku, ili Esc za izlazak iz programa. \n"; //Skontati kako detektovati Esc
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