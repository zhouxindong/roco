#include "utility/easy_signal.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace roco;

std::string func(double)
{
	std::cout << "std::string func(double)\n";
	return "func";
}

auto l = [](double) -> std::string 
{
	std::cout << "lambda: double -> std::string\n";
	return "lambda";
};

class Bar
{
public:
	std::string operator()(double) const
	{
		std::cout << "Bar::operator()(double)\n";
		return "operator()";
	}

	std::string foo(double) const
	{
		std::cout << "Bar::foo -> double:std::string\n";
		return "Bar::foo()";
	}
};

int main()
{
	Easy_signal<std::string(double)> sig;
	auto conn1 = sig.connect(func);
	auto conn2 = sig.connect(l);
	auto conn3 = sig.connect(Bar());
	Bar b;
	auto conn4 = sig.connect(&Bar::foo, b);
	sig(3.22);

	system("pause");
	conn1(2);
	conn2(3);
	conn3(4);
	conn4(2);

	system("pause");
	conn1.disconnect();
	conn2.disconnect();
	conn3.disconnect();
	conn4.disconnect();
	conn3.disconnect();

	sig(2.32);
}