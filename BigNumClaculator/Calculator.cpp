#include "Calculator.h"
#include "Integer.h"
#include "Decimal.h"
#include "Operator.h"
#include <iostream>
using namespace Operator;

map<string, int> Calculator::isp = { { "+", 1 },{ "-", 1 },{ "*", 2 },{ "/", 2 },{ "s-", 4 },{ "^", 6 },{ "Power", 8 },{ ",", 8 },{ "!", 9 },{ "(", 10 } };
map<string, int> Calculator::icp = { { "+", 1 },{ "-", 1 },{ "*", 2 },{ "/", 2 },{ "s-", 3 },{ "^", 5 },{ "Power", 7 },{ ",", -1 },{ "!", 9 },{ "(", 0 } };
map<string, Number*> Calculator::variable;
Calculator::Calculator(string str)
	:op(str)
{
	splitOp();
	decodeOp();
}

void Calculator::setOp(string str)
{
	op = str;
}

void Calculator::splitOp()
{
	string temp;
	string tempOp;
	bool isWord = false;
	bool preOp = true;
	for (auto it = begin(op); it != end(op); ++it)
	{
		if (*it == ' ')
		{
			if (!isWord)
				continue;
			else
			{
				token.push_back(temp);
				temp.clear();
				isWord = false;
			}
		}
		//運算子
		else if (!isdigit(*it) && !isalpha(*it) && *it != '.')
		{
			isWord = false;
			if (!temp.empty())
				token.push_back(temp);
			temp.clear();

			if (preOp && tempOp != "!" && tempOp != ")")
			{
				if (*it == '+')
					continue;
				else if (*it == '-')
				{
					if (tempOp == "-" || tempOp == "s-")
					{
						token[size(token) - 1] = "+";
						tempOp = "+";
					}
						
					else
					{
						token.push_back("s-");
					}
					continue;
				}		
			}
			tempOp.clear();
			tempOp = *it;
			token.push_back(tempOp);
			preOp = true;
		}
		else
		{
			preOp = false;
			if (isalpha(*it))
				isWord = true;
			temp += *it;
		}
	}
	if (!temp.empty())
		token.push_back(temp);
	vector<string> copy;
	bool isNeg = false;
	for (auto it = begin(token); it != end(token); ++it)
	{
		if (*it == "s-" && !isOperator(*(it + 1)))
		{
			copy.push_back("(");
			isNeg = true;
		}
		else if (isNeg && isOperator(*it) && icp[*it] <= icp["s-"])
		{
			copy.push_back(")");
			isNeg = false;
		}
			copy.push_back(*it);
	}
	if (isNeg)
		copy.push_back(")");
	token = copy;
}

std::string Calculator::calculate()
{
	stack<string> s;
	vector<string> postfix;
	
	for (auto &str : token)
	{
		if (isOperator(str))
		{
			if (str == "Power" || str == "power")
				continue;
			if (s.empty())
			{
				s.push(str);
				continue;
			}
			
			if (str == ")")
			{
				while (s.top() != "(")
				{
					postfix.push_back(s.top());
					s.pop();
					if (s.empty())
						throw "遺漏左括號";
				}
				s.pop();
			}
			else if (str == ",")
			{
				while (s.top() != "(")
				{
					postfix.push_back(s.top());
					s.pop();
					if (s.empty())
						throw "Power錯誤";
				}
				s.push(",");
			}
			else if (isp[str] > icp[s.top()])
				s.push(str);
			else if (isp[str] <= icp[s.top()])
			{
				string top = s.top();
				postfix.push_back(top);
				s.pop();
				
				while (!s.empty())
				{
					if (isp[str] <= icp[s.top()])
					{
						top = s.top();
						postfix.push_back(s.top());
						s.pop();
					}
					else
						break;
				}
				s.push(str);
			}
		}
		else
			postfix.push_back(str);
	}
	while (!s.empty())
	{
		postfix.push_back(s. top());
		s.pop();
	}
	stack<Number> num;
	for (const auto &it : postfix)
	{
		if (isOperator(it))
			num.push(operation(it, num));
		else
		{
			if (isalpha(it.front()))
			{
				auto i = variable.find(it);
				if (i == end(variable))
					throw "未定義變數";
				else
					num.push(*variable[it]);
			}
			else
				num.push(Number(it));
		}

	}
	if (num.size() != 1)
		throw "非法運算式";
	ansNumber = num.top();
	answer = num.top().getNumber();
	return answer;
}

string Calculator::getAnswer() const
{
	return answer;
}

Number Calculator::getAnsNumber() const
{
	return ansNumber;
}

Calculator::~Calculator()
{
}

void Calculator::decodeOp()
{
	if (token.empty())
		return;
	//input: Set ....
	else if (token[0] == "Set" || token[0] == "set")
	{
		token.erase(begin(token), begin(token) + 1);
		setVariable();
	}
	//input: variable
	else if (isalpha(token[0][0]) && size(token) == 1)
	{
		auto i = variable.find(token[0]);
		if (i == end(variable))
			throw "未定義變數";
		calculate();
		
	}
	//input: variable = .....
	else if (isalpha(token[0][0]) && token[1] == "=" && token[0] != "s-")
	{
		if (size(token) < 3)
			throw "格式錯誤";
		
		string name = token[0];
		if (variable.find(name) == end(variable))
			throw "未定義變數";

		token.erase(begin(token), begin(token) + 2);
		variable[name]->setNumber(calculate());
		answer.clear();
	}
	else
		calculate();
}

void Calculator::setVariable()
{
	//input: Type variable = ....
	if (token.empty() || token.size() < 4 || token[2] != "=")
		throw "設定變數錯誤";
	
	string type = token[0];
	string name = token[1];
	token.erase(begin(token), begin(token) + 3);
	if (type == "Integer" || type == "integer")
	{
		Integer *temp = new Integer(calculate());
		variable[name] = temp;
		answer.clear();
	}
	else if (type == "Decimal" || type == "decimal")
	{
		string tem;
		for (const auto &str : token)
			tem += str;
		Decimal *temp = new Decimal(tem);
		variable[name] = temp;
		answer.clear();
	}
	else
		throw "設定變數錯誤";
}

bool Calculator::isOperator(string str)
{
	if (str == "Power" || str == "power" || str == "s-")
		return true;
	
	if (!isdigit(str[0]) && !isalpha(str[0]) && size(str) == 1)
	{
		if (str == "+" || str == "-" || str == "*" || str == "/" ||
			str == "^" || str == "," || str == "!" || str == "(" || str == ")")
			return true;
		else
			throw "非法運算子";
	}
	else
		return false;
}

Number Calculator::operation(string str, stack<Number>& s)
{
	if (s.empty())
		throw "非法運算式";
	auto b = s.top();
	s.pop();
	if (str == "!")
		return factorial(b);
	else if (str == "s-")
		return negative(b);
	if (s.empty())
		throw "非法運算式";

	auto a = s.top();
	s.pop();

	if (str == "+")
		return a + b;
	else if (str == "-")
		return a - b;
	else if (str == "*")
		return a * b;
	else if (str == "/")
		return a / b;
	else if (str == "^" || str == ",")
		return pow(a, b);
}
