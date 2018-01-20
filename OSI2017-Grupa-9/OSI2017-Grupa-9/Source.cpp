#include "AssistFunc.h"
#include "Administrator.h"


void main()
{
	SetFileAttributesA("Program Files", FILE_ATTRIBUTE_HIDDEN);
	SetFileAttributesA("Racuni za ispis.txt", FILE_ATTRIBUTE_HIDDEN);
	::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);	//fullscreen konzola, izgleda da w7 ovo cudo ne podrzava
	//system("mode 650"); //ne radi na win10
	runIt();
}