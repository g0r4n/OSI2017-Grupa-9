#include "AssistFunc.h"
#include "Administrator.h"

void main()
{
	std::fstream file("test.txt", std::ios::in | std::ios::out);
	runIt();
	file.close();
}