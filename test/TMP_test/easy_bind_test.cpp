// TMP_test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "TMP/easy_bind.hpp"
#include <string>
#include <typeinfo>

std::string fun0()
{
    return "fun0";
}

std::string fun1(double)
{
    return "fun1";
}

class functor0
{
public:
    std::string operator()() const
    {
        return "functor0::operator()";
    }

    std::string bar() const
    {
        return "functor0::bar()";
    }
};

int main()
{
    std::cout << typeid(roco::detail::build_indices<1>).name() << "\n";
    std::cout << typeid(roco::detail::indices<0>).name() << "\n";

    //roco::detail::show(roco::detail::build_indices<3>());
    //auto vec = roco::detail::make_index_vector(std::make_index_sequence<10>());
    //for (auto i : vec)
    //{
    //    std::cout << i << ' ';
    //}
    //std::cout << std::endl;

	auto vec = roco::detail::make_index_vector(roco::detail::build_indices<10>());
	for (auto i : vec)
	{
		std::cout << i << ' ';
	}
	std::cout << std::endl;

    auto placeholders = roco::detail::gen_placeholders(roco::detail::build_indices<2>());
    std::cout << std::tuple_size<decltype(placeholders)>::value << "\n";
    auto i1 = std::get<0>(placeholders);
    std::cout << i1.value << "\n";
    auto i2 = std::get<1>(placeholders);
    std::cout << i2.value << "\n";
    int i = 0;

    std::cout << typeid(std::tuple_element<0, decltype(placeholders)>::type).name() << "\n";
    //auto f = roco::easy_bind(&functor0::bar, functor0());
    //std::cout << f() << "\n";

    //auto f1 = roco::easy_bind(fun1);
    //std::cout << f1(3.2) << "\n";

    //f = roco::easy_bind((std::string(*)())&functor0::bar);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
