#pragma once
#include "IPrintable.h"
#include "IReadable.h"
#include "usedLibs.h"

namespace user
{
	class User: virtual public IPrintable, virtual public IReadable
	{
	protected:
		std::tuple<string, string, string, bool> userInfo;	//ime, prezime, PIN, korisnicka grupa(0-ADMIN, 1-ANALITICAR)
	public:
		User();
		User(const std::tuple<string, string, string, bool>&);
		/*	copy i move konstruktori zajedno sa operatorima dodjele
			su nepotrebni zato sto je jedino polje tipa std::tuple<>
			koji ima definisane svoje operatore dodjele i copy i move konstruktore	*/
		~User();
	
		bool operator<(const User&) const;
		bool operator>(const User&) const;
		bool operator==(const User&) const;
		
		//provjeriti da li je potrebno na ovaj nacin realizovati upis i ispis
		//pokusati napraviti posebne metode za ispis u fajl a ove nasljedjene napraviti tako da ispisuju informacije o korisnicima
		void print(std::ostream&) const override;
		void read(std::istream&) override;
	};
}