#pragma once
#include "Number.h"
#include <string>
#include <stack>
#include <vector>
#include <map>
using namespace std;

class Calculator
{
public:
	Calculator(string = "0");
	void setOp(string);
	void splitOp();
	string calculate();
	string getAnswer() const;
	Number getAnsNumber() const;
	~Calculator();

private:
	string op;
	vector<string> token;
	Number ansNumber;
	string answer;
	static map<string, int> isp;  //in stack priority
	static map<string, int> icp;  //int container priority
	void decodeOp();
	void setVariable();
	bool isOperator(string);
	Number operation(string, stack<Number>&);
	static map<string, Number*> variable;
};

