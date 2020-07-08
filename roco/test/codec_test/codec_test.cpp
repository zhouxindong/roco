// codec_test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "codec/code_converter.hpp"
#include "assert/assert_any.hpp"

using namespace std;
using namespace roco;

int main()
{
	std::string s_ansi = "VDR域";
	std::string s_utf8 = u8"VDR域";
	std::wstring ws = L"VDR域";

	std::string s2_utf8 = Code_converter::ansi_to_utf8(s_ansi);
	ASSERT_ANY(s2_utf8 == s_utf8);

	std::string s2_ansi = Code_converter::utf8_to_ansi(s_utf8);
	ASSERT_ANY(s2_ansi == s_ansi);

	std::cout << "ansi: " << ::strlen(s_ansi.c_str()) << ", size=" << sizeof(s_ansi) << "\n";
	std::cout << "utf8: " << ::strlen(s_utf8.c_str()) << ", size=" << sizeof(s_utf8) << "\n";
	std::cout << "wchar: " << ::lstrlenW(ws.c_str()) << ", size=" << sizeof(ws) << "\n";
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
