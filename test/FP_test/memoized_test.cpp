#include <iostream>
#include "FP/memoized.hpp"
#include <chrono>

using namespace std;
using namespace roco;

unsigned int fib(unsigned int n)
{
	if (n == 1)
		return 1;
	else if (n == 2)
		return 1;
	else
		return fib(n - 1) + fib(n - 2);
}

//int main()
//{
//	auto fibmemo = make_memoized(fib);
//
//	std::chrono::steady_clock::time_point t1 =
//		std::chrono::steady_clock::now();
//	std::cout << "fib(30) = " << fibmemo(30) << "\n";
//	std::chrono::steady_clock::time_point t2 =
//		std::chrono::steady_clock::now();
//	std::cout << "duration = "
//		<< std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count()
//		<< "\n";
//	std::cout << "fib(30) = " << fibmemo(30) << "\n";
//	std::chrono::steady_clock::time_point t3 =
//		std::chrono::steady_clock::now();
//	std::cout << "duration = "
//		<< std::chrono::duration_cast<std::chrono::microseconds>(t3 - t2).count()
//		<< "\n";
//}