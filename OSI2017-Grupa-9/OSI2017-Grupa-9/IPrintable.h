#pragma once
#include "AssistFunc.h"

class IPrintable
{
	friend std::ostream& operator << (std::ostream&, IPrintable&);
public:
	virtual void print(std::ostream&) const = 0;
};

