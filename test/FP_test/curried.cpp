#include "FP/curried.hpp"
#include <iostream>
#include <string>

void print_it(double d, std::string s, int i)
{
	std::cout << "double: " << d;
	std::cout << ", string: " << s;
	std::cout << ", int: " << i << "\n";
}

class callable_test {
public:
	template <typename T1, typename T2, typename T3>
	auto operator() (T1 x, T2 y, T3 z) const
	{
		return x + y + z;
	}

	template <typename T1, typename T2>
	auto operator() (T1 x, T2 y) const
	{
		return x + y;
	}

};

int main()
{
	//auto print_it_cd = roco::make_curried(print_it);

	auto less_curried = roco::make_curried(std::less<>());

	auto ret1 = less_curried(42, 1);

	auto greater_than_42 = less_curried(42);
	auto ret2 = greater_than_42(1.0);
	auto ret3 = greater_than_42(100.0);

	callable_test ct;

	auto ct_curried = roco::make_curried(ct);
	auto ret4 = ct_curried(1)(2, 3);

	auto ct_curried_one = ct_curried(1);

	auto ret5 = ct_curried_one(2, 3);
}