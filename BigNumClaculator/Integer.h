#pragma once
#include "Number.h"

class Integer : public Number
{
public:
	Integer(string = "");
	Integer(const char*);
	Integer(const Number&);
	void setNumber(string);
	string getNumber() const;
	~Integer();
	
private:
	string getNumerator() const;
	istream & setNum(istream&);
	ostream & printNum(ostream&) const;
};

