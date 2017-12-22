#include "AssistFunc.h"
#include "Administrator.h"

void main()
{
	
	auto log = logIn();
	if (std::get<4>(log) == 1)
	{
		admin::Administrator a1(log);
		cout << a1;
		getchar();
	}
}