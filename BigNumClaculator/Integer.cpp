#include "Integer.h"
#include "Calculator.h"
Integer::Integer(string num)
{
	setNumber(num);
}

Integer::Integer(const char* n)
{
	setNumber(n);
}

Integer::Integer(const Number& a)
{
	setNumber(a.getNumber());
}

void Integer::setNumber(string n)
{
	Calculator temp(n);
	numerator = temp.getAnswer().substr(0, n.find('.'));
	denominator = "1";
}

std::string Integer::getNumber() const
{
	return getNumerator();
}

Integer::~Integer()
{
}

std::string Integer::getNumerator() const
{
	return numerator.substr(0, numerator.find('.'));
}

std::istream & Integer::setNum(istream& is)
{
	return is >> this->numerator;
}

std::ostream & Integer::printNum(ostream& os) const
{
	return os << this->getNumber();
}
