#include "Decimal.h"
#include "Calculator.h"

Decimal::Decimal(string num)
{
	setNumber(num);
}

Decimal::Decimal(const char* n)
{
	setNumber(n);
}

Decimal::Decimal(const Number& n)
{
	numerator = n.getNumerator();
	denominator = n.getDenominator();
}

void Decimal::setNumber(string n)
{
	Calculator temp(n);
	numerator = temp.getAnsNumber().getNumerator();
	denominator = (temp.getAnsNumber() * Number("1.0")).getDenominator();
}

std::istream & Decimal::setNum(istream& is)
{
	return is >> this->numerator;
}

std::ostream & Decimal::printNum(ostream& os) const
{
	return os << this->getNumber();
}
