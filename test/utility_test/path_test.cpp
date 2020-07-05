#include <iostream>
#include "utility/path.hpp"

using namespace roco;

int main()
{
	std::cout << Path::pwd() << "\n";
	system("pause");
	return 0;
}