#pragma once
#include <string>
namespace Operator
{
	bool compare(const std::string&, const std::string&);
	std::string add(std::string, std::string);
	std::string sub(std::string, std::string);
	std::string mult(std::string, std::string);
	std::string div(std::string, std::string);
	std::string power(std::string, std::string);
	std::string sqrt(std::string);
	std::string factorial(std::string);
}