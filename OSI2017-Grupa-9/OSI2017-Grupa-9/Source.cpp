#include "AssistFunc.h"
#include "Administrator.h"
#include "Bill.h"

void main()
{
	
	::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);	//fullscreen konzola, izgleda da w7 ovo cudo ne podrzava
	//system("mode 650"); ne radi na win10
	std::fstream file("test.txt", std::ios::in | std::ios::out);
	runIt();
	file.close();
	/*system("mode 650");
	Bill::Date date(12, 02, 2015);
	Bill::Product t1("Burek", 2, 10, 20);
	Bill::Product t2("Jogurt", 3.20, 2, 6.40);
	std::vector<Bill::Product> vec;
	vec.push_back(t1); vec.push_back(t2);
	Bill BILI("Nikola Tramosljika", date, vec);
	cout << std::resetiosflags(std::ios::adjustfield);			// resetovanje 
	cout << std::setiosflags(std::ios::left);					// poravnanje u lijevo
	cout
		<< std::setw(15)
		<< "Datum"
		<< std::setw(20)
		<< "Kupac"
		<< std::setw(19)
		<< "Proizvod"
		<< std::setw(10)
		<< "Cijena"
		<< std::setw(10)
		<< "PDV(17%)"
		<< std::setw(10)
		<< "Kolicina"
		<< std::setw(10)
		<< "Ukupno"
		<< std::setw(15)
		<< "Ukupno sa PDV-om" << endl;
	BILI.writeBillToConsole();
	getchar();*/
	
	

}