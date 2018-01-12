
#pragma once
#include "AssistFunc.h"
#include "User.h"


namespace analiticar
{
	class Analiticar : public user::User
	{

	public:

		Analiticar();
		Analiticar(const std::tuple<string, string, string, string, bool>&);
		~Analiticar();

		void billsDateOverview();
		void billsProductOverview();
		void billsBuyerOverview();
		int menu();

	};
}