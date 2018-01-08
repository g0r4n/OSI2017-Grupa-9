#include "AssistFunc.h"
#include "Administrator.h"

void main()
{
	//::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);	//fullscrean konzola
	std::fstream file("test.txt", std::ios::in | std::ios::out);
	runIt();
	file.close();
}