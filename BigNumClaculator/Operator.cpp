#include "Operator.h"
#include <stdexcept>

#include <algorithm>
#include <vector>
using std::string;
string __add(string a, string b);
string __sub(string a, string b);
int findPoint(const string&);

bool isZero(const string &a)
{
	for (const auto &c : a)
		if (c != '0' && c != '.' && c != '-')
			return false;
	return true;
}
void removeLeadingZero(string &a)
{
	auto it = begin(a);
	int i = 0;
	if (*it == '-')
	{
		it++;
		i = 1;
	}
	for (; it != end(a); ++it)
	{
		if (*it == '.')
		{
			a.erase(begin(a) + i, it - 1);
			return;
		}
		else if (*it != '0' && *it != '-')
		{
			a.erase(begin(a) + i, it);
			return;
		}
	}
}
void removeBackingZero(string &a)
{
	if (a.find('.') == string::npos)
		return;
	reverse(begin(a), end(a));
	removeLeadingZero(a);
	reverse(begin(a), end(a));
}
//a >= b return true
bool Operator::compare(const string &a, const string &b)
{
	int aPos = findPoint(a);
	int bPos = findPoint(b);
	if (aPos == 0)
		aPos = size(a);
	if (bPos == 0)
		bPos = size(b);
	if (aPos == bPos)
	{
		for (int i = 0; i < aPos; ++i)
		{
			if (a[i] == b[i])
				continue;
			else
				return a[i] > b[i];
		}
		for (int i = aPos;; ++i)
		{
			if (i >= size(b))
				return true;
			else if (i >= size(a))
				return false;
			else if (a[i] == b[i])
				continue;
			else
				return a[i] > b[i];
		}
	}
	else
		return aPos > bPos;
}
bool isNegative(string &a)
{
	if (a.front() == '-')
	{
		a.erase(begin(a));
		return true;
	}
	else
		return false;
}
int findPoint(const string& a)
{
	int point = find(begin(a), end(a), '.') - begin(a);
	if (point == size(a))
		return 0;
	else
		return point;
}
void fillZero(string& a, string& b)
{
	reverse(begin(a), end(a));
	reverse(begin(b), end(b));
	if (a.back() == '-')
		a.pop_back();
	if (b.back() == '-')
		b.pop_back();
	int aPoint = findPoint(a);
	int bPoint = findPoint(b);

	int maxFloatLen = std::max(aPoint, bPoint);
	if (maxFloatLen > aPoint)
	{
		string temp(maxFloatLen - aPoint, '0');
		if (aPoint == 0)
			a = '.' + a;
		a = temp + a;
		
	}
	else if (maxFloatLen > bPoint)
	{
		string temp(maxFloatLen - bPoint, '0');
		if (bPoint == 0)
			b = '.' + b;
		b = temp + b;
		
	}
	int maxIntLen = std::max(size(a), size(b));
	if (maxIntLen > size(a))
	{
		string temp(maxIntLen - size(a), '0');
		a += temp;
	}
	else if (maxIntLen > size(b))
	{
		string temp(maxIntLen - size(b), '0');
		b += temp;
	}
}
string reverseAndFormat(string &str)
{
	reverse(begin(str), end(str));
	auto it = begin(str);
	int leadingZero = 0;
	for (const auto &c : str)
	{
		if (c == '.')
		{
			str.erase(begin(str), begin(str) + leadingZero - 1);
			return str;
		}
		else if (c != '0')
		{
			str.erase(begin(str), begin(str) + leadingZero);
			return str;
		}
		else
			leadingZero++;
	}
	return "0";
} 
std::string Operator::add(string a, string b)
{
	bool na = isNegative(a), nb = isNegative(b);
	if (na && nb)
		return "-" + __add(a, b);
	else if (!na && nb)
		return __sub(a, b);
	else if (na && !nb)
		return __sub(b, a);
	else
		return __add(a, b);
}

std::string Operator::sub(string a, string b)
{
	bool na = isNegative(a), nb = isNegative(b);
	if (na && nb)
		return __sub(b, a);
	else if (!na && nb)
		return __add(a, b);
	else if (na && !nb)
		return "-" + __add(a, b);
	else
		return __sub(a, b);
}
string __add(string a, string b)
{
	fillZero(a, b);
	string result(size(a), ' ');
	int carry = 0, sum = 0;
	for (int i = 0; i < size(a); ++i)
	{
		if (a[i] == '.')
		{
			result[i] = '.';
			continue;
		}
		sum = a[i] - '0' + b[i] - '0' + carry;
		carry = sum / 10;
		result[i] = sum % 10 + '0';
	}
	if (carry != 0)
		result.push_back('1');
	return reverseAndFormat(result);
}
string __sub(string a, string b)
{
	string sign = "";
	if (!Operator::compare(a, b))
	{
		swap(a, b);
		sign = "-";
	}
	fillZero(a, b);
	string result(size(a), ' ');
	int borrow = 0, dif = 0;
	for (int i = 0; i < size(a); ++i)
	{
		if (a[i] == '.')
		{
			result[i] = '.';
			continue;
		}
		dif = (a[i] - '0') - (b[i] - '0') - borrow;
		if (dif < 0)
		{
			borrow = 1;
			result[i] = dif + 10 + '0';
		}
		else
		{
			borrow = 0;
			result[i] = dif + '0';
		}
	}
	return sign + reverseAndFormat(result);
}

std::string Operator::mult(string a, string b)
{
	if (isZero(a) || isZero(b))
		return "0";
	string sign = "";
	if (isNegative(a) != isNegative(b))
		sign = "-";
	
	removeBackingZero(a);
	removeBackingZero(b);
	reverse(begin(a), end(a));
	reverse(begin(b), end(b));
	int aPoint = findPoint(a);
	int bPoint= findPoint(b);
	
	int pointPos = aPoint + bPoint;
	for (auto it = begin(a); it != end(a); ++it)
		if (*it == '.')
		{
			a.erase(it);
			break;
		}
	for (auto it = begin(b); it != end(b); ++it)
		if (*it == '.')
		{
			b.erase(it);
			break;
		}

	std::vector<int> c(size(a) + size(b), 0);
	for (int i = 0; i < size(a); ++i)
		for (int j = 0; j < size(b); ++j)
			c[i + j] += (a[i] - '0') * (b[j] - '0');

	string result;
	int sum = 0, carry = 0;
	
	for (int i = 0; i < c.size(); ++i)
	{
		if (i == pointPos && pointPos != 0)
			result.push_back('.');
		sum = c[i] + carry;
		carry = sum / 10;
		result.push_back(sum % 10 + '0');
	}

	result = reverseAndFormat(result);
	if (result == "0")
		return "0";
	else
		return sign + result;
}

std::string Operator::div(string a, string b)
{
	for (int i = 0; i <= size(b); ++i)
	{
		if (i == size(b))
			throw"埃计ぃ眔箂";
		if (b[i] != '0' && b[i] != '.')
			break;
	}
	string result;
	string sign = "";
	if (isNegative(a) != isNegative(b))
		sign = "-";
	reverse(begin(a), end(a));
	reverse(begin(b), end(b));
	
	int aPoint = findPoint(a);
	int bPoint = findPoint(b);
	if (aPoint != 0)
		a.erase(begin(a) + aPoint);
	if (bPoint != 0)
		b.erase(begin(b) + bPoint);
	a= reverseAndFormat(a);
	b = reverseAndFormat(b);

	//integer
	string temp = a.substr(0, b.size());
	int shift = b.size();
	int q = 0;
	while (compare(temp, b))
	{
		temp = sub(temp, b);
		q++;
	}
	result.push_back(q + '0');
	while (shift < a.size())
	{
		if (temp == "0")
			temp.clear();
		temp = temp + a[shift++];
		q = 0;
		while (compare(temp, b))
		{
			temp = sub(temp, b);
			q++;
		}
		result.push_back(q + '0');
	}
	int nowPoint = size(result);
	if (aPoint != 0 || bPoint != 0)
	{
		int pointOffset =  bPoint - aPoint;
		for (int i = -pointOffset; i <= 100; ++i)
		{
			if (temp != "0")
				temp.push_back('0');
			q = 0;
			while (compare(temp, b))
			{
				temp = sub(temp, b);
				q++;
			}
			result.push_back(q + '0');
		}
		string temp(aPoint, '0');
		result = temp + result;
		result.insert(begin(result) + nowPoint + bPoint, '.');
	}
	reverse(begin(result), end(result));
	result = reverseAndFormat(result);
	if (result == "0")
		return "0";
	else
		return sign + result;
}

std::string Operator::power(string a, string b)
{
	//special case
	if (isZero(b))  // x^0
		return "1";
	if (isZero(a))  //0^x
		return "0";
	if (isZero(sub(a, "1")))
	{
		if (b.find('.') == string::npos)
			return a;
		else if (a.find('.') == string::npos && b.find('.') != string::npos)
			return a + ".0";
	}
		

	if (a.find('.') == string::npos && b.find('.') != string::npos)
		a += ".0";
	string result(a);
	auto it = find(begin(b), end(b), '.');
	if (it != end(b))
	{
		it++;
		bool needSqrt = false;
		if (*it != '0' && *it != '5')
			throw "计岿粇";
		if (*it == '5')
		{
			needSqrt = true;
			b = mult(b, "2");
		}
			
		b = b.substr(0, it - begin(b));
		double exp = stod(b);
		for (int i = 2; i <= exp; ++i)
			result = mult(result, a);
		if (needSqrt)
			result = sqrt(result);
	}
	else
	{
		int exp = stoi(b);
		for (int i = 2; i <= exp; ++i)
			result = mult(result, a);
	}
	return result;
}
string abs(const string &n)
{
	if (n[0] == '-')
		return n.substr(1, size(n) - 1);
	else
		return n;
}
std::string Operator::sqrt(string n)
{
	if (isNegative(n))
		throw "腹瞷璽计";
	if (isZero(n))
		return "0";
	if (isZero(sub(n, "1")))
		return n;
	string n0 = mult(n, "0.5");
	string n1 = mult("0.5", add(n0, div(n, n0)));
	string err = "0." + string(99, '0') + "1";

	while (compare(abs(sub(n0, n1)), err))
	{
		n0 = n1;
		n1 = mult("0.5", add(n0, div(n, n0)));
	}

	int point = find(begin(n1), end(n1), '.') - begin(n1);
	if (point + 100 < size(n1))
		return n1.substr(0, point + 103);
	else
		return n1;
}

std::string Operator::factorial(string a)
{
	bool isDecimal = false;
	for (auto it = begin(a); it != end(a); ++it)
	{
		if (*it == '.')
			isDecimal = true;
		else if (isDecimal && *it != '0')
			throw "顶ぃ眔计";
		else if (!isdigit(*it) || *it == '-')
			throw "顶ぃ眔璽计";
	}
	
	a = a.substr(0, find(begin(a), end(a), '.') - begin(a));
	string result = "1";
	for (int i = 1; i <= stoi(a); ++i)
		result = mult(result, std::to_string(i));

	return result;
}
