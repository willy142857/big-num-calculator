#pragma once
#include "Number.h"

class Decimal : public Number
{
public:
	Decimal(string = "");
	Decimal(const char*);
	Decimal(const Number&);
	void setNumber(string);
private:
	istream & setNum(istream&);
	ostream & printNum(ostream&) const;
};

