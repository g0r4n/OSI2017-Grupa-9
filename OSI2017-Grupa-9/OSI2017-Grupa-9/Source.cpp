#include "AssistFunc.h"
#include "Administrator.h"

void main()
{
	std::fstream file("test.txt", std::ios::in | std::ios::out);
	/*auto log = logIn();
	if (std::get<4>(log))
	{
		admin::Administrator a1(log);
		a1.menu();
	}*/
	runIt();
	file.close();

	getchar();
}