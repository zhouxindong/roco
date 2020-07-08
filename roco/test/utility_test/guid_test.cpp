#include <iostream>
#include "utility/guid.hpp"
#include <unordered_set>

using namespace roco;

//int main()
//{
//	using ull = unsigned long long;
//	ull first_loop = 1;
//	ull second_loop = 1000;
//	std::unordered_set<std::string> bucket;
//	for (ull i = 0; i < first_loop; ++i)
//	{
//		bucket.clear();
//		for (ull j = 0; j < second_loop; ++j)
//		{
//			std::string gid = guid_hex(32);
//			if (bucket.find(gid) != bucket.end())
//			{
//				std::cout << "i = " << i << ", j = " << j << "depulited!\n";
//				system("pause");
//				return 0;
//			}
//
//			bucket.insert(gid);
//		}
//	}
//	std::cout << "first loop = " << first_loop << ", second loop = " << second_loop << "\n";
//	return 0;
//}