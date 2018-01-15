#include "AssistFunc.h"
#include "Administrator.h"
#include "Bill.h"

void main()
{
	
	//::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);	//fullscreen konzola, izgleda da w7 ovo cudo ne podrzava
	system("mode 650"); //ne radi na win10
	std::fstream file("test.txt", std::ios::in | std::ios::out);
	runIt();
	file.close();
	
}