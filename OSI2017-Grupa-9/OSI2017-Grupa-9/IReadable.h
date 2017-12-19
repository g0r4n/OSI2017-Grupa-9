#pragma once
#include "AssistFunc.h"

class IReadable
{
	friend std::istream& operator >> (std::istream&, IReadable&);
public:
	virtual void read(std::istream&) = 0;
};

