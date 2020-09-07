#include "utility/easy_signal.hpp"
#include <iostream>
#include <string>
#include <numeric>

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

int func2()
{
	return 3;
}

class Bar2
{
public:
	int operator()() const
	{
		return 10;
	}

	int Foo2() const
	{
		return 21;
	}
};

int sum_agg(const std::vector<int>& v)
{
	return std::accumulate(v.cbegin(), v.cend(), 0);
}

int main()
{
	// 1. basic
	//Easy_signal<std::string(double)> sig;
	//auto conn1 = sig.connect(func);
	//auto conn2 = sig.connect(l);
	//auto conn3 = sig.connect(Bar());
	//Bar b;
	//auto conn4 = sig.connect(&Bar::foo, b);
	//sig(3.22);

	//system("pause");
	//conn1(2);
	//conn2(3);
	//conn3(4);
	//conn4(2);

	//system("pause");
	//conn1.disconnect();
	//conn2.disconnect();
	//conn3.disconnect();
	//conn4.disconnect();
	//conn3.disconnect();

	//sig(2.32);

	//std::cout << "any key to reconnect\n";
	//system("pause");
	//conn2.reconnect();
	//sig(2.3);
	//system("pause");

	//conn1.reconnect();
	//conn4.reconnect();
	//conn3.reconnect();
	//sig(3.0);

	// 2. connect to signal
	//Easy_signal<std::string(double)> sig;
	//auto conn1 = sig.connect(func);
	//auto conn2 = sig.connect(l);
	//auto conn3 = sig.connect(Bar());

	//Easy_signal<std::string(double)> sig2;
	//Bar b;
	//auto conn4 = sig2.connect(&Bar::foo, b);

	//sig.connect(sig2);

	//sig(3.2);

	// 3. retrive the connect results
	Easy_signal<int()> sig;
	sig.connect(func2);
	sig.connect([]() {return 33; });
	sig.connect(Bar2());
	Bar2 b2;
	sig.connect(&Bar2::Foo2, b2);
	std::cout << sig.emit_result_back(sum_agg) << "\n";
}