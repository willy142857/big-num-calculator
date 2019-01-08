#pragma once
#include <iostream>
#include <string>
using namespace std;

class Number
{
public:
	Number(string="");
	virtual void setNumber(string);
	virtual string getNumber() const;
	virtual string getNumerator() const;
	virtual string getDenominator() const;
	~Number();

	friend Number operator+(const Number&, const Number&);
	friend Number operator-(const Number&, const Number&);
	friend Number operator*(const Number&, const Number&);
	friend Number operator/(const Number&, const Number&);
	friend Number pow(const Number&, const Number&);
	friend Number sqrt(const Number&);
	friend Number factorial(const Number&);
	friend Number negative(const Number&);

	friend istream &operator>>(istream&, Number&);
	friend ostream &operator<<(ostream&, const Number&);
	
protected:
	string numerator;  //¤À¤l
	string denominator; //¤À¥À
	
private:
	virtual istream& setNum(istream&);
	virtual ostream& printNum(ostream&) const;
};

