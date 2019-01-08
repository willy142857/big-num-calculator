#include "Number.h"
#include "Operator.h"
using namespace Operator;

Number::Number(string num)
	:denominator("1.0")
{
	setNumber(num);
}

void Number::setNumber(string n)
{
	if (!n.empty())
	{
		numerator = n;
		if (n.find('.') != string::npos)
			denominator = "1.0";
		else
			denominator = "1";
	}
}

std::string Number::getNumber() const
{
	string n = div(getNumerator(), denominator);
	int count = -1;
	bool isFloat = false;
	for (auto it = begin(n); it != end(n); ++it)
	{
		if (*it == '.' || isFloat)
		{
			count++;
			isFloat = true;
		}
		if (count == 100)
			return n.substr(0, it - begin(n) + 1);
	}
	if (!isFloat)
		return n;
	else
	{
		string temp(100 - count, '0');
		return n + temp;
	}
}

std::string Number::getNumerator() const
{
	return numerator;
}

std::string Number::getDenominator() const
{
	return denominator;
}

std::istream& Number::setNum(istream& is)
{
	return is >> this->numerator;
}

Number::~Number()
{
}

std::ostream& Number::printNum(ostream& os) const
{
	return os << this->getNumber();
}

Number operator+(const Number& a, const Number&b)
{
	Number result;
	result.denominator = mult(a.denominator, b.denominator);
	string numA = mult(a.getNumerator(), b.denominator);
	string numB = mult(b.getNumerator(), a.denominator);
	result.numerator = add(numA, numB);
	return result;
}

Number operator-(const Number& a, const Number&b)
{
	Number result;
	result.denominator = mult(a.denominator, b.denominator);
	string numA = mult(a.getNumerator(), b.denominator);
	string numB = mult(b.getNumerator(), a.denominator);
	result.numerator = sub(numA, numB);
	return result;
}

Number operator*(const Number& a, const Number&b)
{
	Number result;
	
	result.numerator = mult(a.getNumerator(), b.getNumerator());
	result.denominator = mult(a.denominator, b.denominator);
	return result;
}

Number operator/(const Number& a, const Number&b)
{
	Number result;
	if (a.denominator == "1" && b.denominator == "1")
	{
		result.numerator = div(a.getNumerator(), b.getNumerator());
		result.denominator = "1";
	}
	else
	{
		result.numerator = mult(a.getNumerator(), b.denominator);
		result.denominator = mult(a.denominator, b.getNumerator());
	}
	return result;
}

Number pow(const Number& a, const Number& b)
{
	Number result;
	string numB = b.getNumber();
	if (numB.front() == '-')
	{
		numB.erase(begin(numB));
		result.numerator= power(a.denominator, numB);
		result.denominator = power(a.numerator, numB);
	}
	else
	{
		result.numerator = power(a.numerator, numB);
		result.denominator = power(a.denominator, numB);
	}
	return result;
}

Number sqrt(const Number& a)
{
	Number result;
	result.denominator = "1.0";
	string n = a.getNumber();
	string n0 = mult(n, "0.5");
	string n1 = mult("0.5", add(n0, div(n, n0)));
	string eps = "0." + string(1, '0') + "1";
	for (int i = 0; i < 20; ++i)
	{
		n0 = n1;
		n1 = mult("0.5", add(n0, div(n, n0)));
	}
	
	int point = find(begin(n1), end(n1), '.') -begin(n1);
	if (point + 100 < size(n1))
		result.numerator = n1.substr(0, point + 100);
	else
		result.numerator = n1;
	return result;
}

Number factorial(const Number& a)
{
	Number result;
	result.numerator = factorial(a.getNumber());
	if (a.denominator.find('.') != string::npos)
		result.denominator = "1.0";
	else
		result.denominator = "1";
	return result;
}

Number negative(const Number& a)
{
	Number result(a);
	if (a.getNumber()[0] == '-')
		result.numerator.erase(begin(result.numerator));
	else
		result.numerator = "-" + result.numerator;
		
	return result;
}
istream &operator>>(istream& in, Number& n)
{
	return n.setNum(in);
}
ostream &operator<<(ostream& out, const Number& n)
{
	return n.printNum(out);
}
