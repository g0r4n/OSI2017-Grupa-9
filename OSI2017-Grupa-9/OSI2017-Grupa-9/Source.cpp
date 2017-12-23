#include "AssistFunc.h"
#include "Administrator.h"

void main()
{
	std::fstream file("C:\\test.txt", std::ios::in | std::ios::out);
	admin::Administrator a1({ "goci","Goran","Marinkovic","6462",1 });
	int n;
	cout << "n: "; cin >> n; cin.ignore();
	while (n--)
		a1.addNewUser(file);
	file.close();
	getchar();
}