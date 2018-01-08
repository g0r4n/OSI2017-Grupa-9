#pragma once
#include "IPrintable.h"
#include "IReadable.h"
#include "AssistFunc.h"

namespace user
{
	class User: virtual public IPrintable, virtual public IReadable
	{
	protected:

		std::tuple<string,string, string, string, bool> userInfo;			//ime, prezime, PIN, korisnicka grupa(0-ADMIN, 1-ANALITICAR)


	public:

		User();
		User(const std::tuple<string,string, string, string, bool>&);
		~User();
		
		string getUserName() const;

		void setUserName(const string&);
		void setName(const string&);
		void setSureName(const string&);
		void setPIN(const string&);
		void setUserGroup(const bool&);

		bool operator<(const User&) const;
		bool operator>(const User&) const;
		bool operator==(const User&) const;
		
		
		void print(std::ostream&) const override;
		void read(std::istream&) override;
	};
}