// parse_test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "codec/gbk_utf8.hpp"
//#include "parse/nlohmann_json.hpp"

//using json = nlohmann::json;

// create a json object
//int main()
//{
//	json j;
//	j["pi"] = 3.141;
//	j["happy"] = true;
//	j["name"] = "Niels";
//	j["nothing"] = nullptr;
//	j["answer"]["everything"] = 42; // object
//	j["list"] = { 1,0,2 }; // array
//	j["object"] = { {"currency", "USD"}, {"value", 42.99} }; // object
//	std::cout << j << std::endl;
//
//	json j2 = {
//		{"pi", 3.141},
//		{"happy", true},
//		{"name", "Niels"},
//		{"nothing", nullptr},
//		{"answer", {
//			{"everything", 42}
//		}},
//		{"list", {1, 0, 2}},
//		{"object", {
//			{"currency", "USD"},
//		{"value", 42.99}
//		}}
//	};
//	std::cout << j2 << std::endl;
//
//	json empty_array_explicit = json::array();
//	json empty_object_implicit = json({});
//	json empty_object_explicit = json::object();
//
//	// [["currency", "USD"],["value", 42.99]]
//	json array_not_object = json::array({ {"currency", "USD"},
//		{"value", 42.99} });
//}

// to/from strings
//int main()
//{
//	json j = R"(
//{
//	"happy": true,
//	"pi": 3.141
//}
//)"_json;
//	std::string s = j.dump();
//	std::cout << s << std::endl;
//
//	auto j2 = json::parse("{ \"happy\": true, \"pi\": 3.141 }");
//	std::cout << j2.dump(4) << std::endl;
// }

//int main()
//{
//	// store a string in a JSON value
//	json j_string = "this is a string";
//
//	// retrieve the string value
//	auto cpp_string = j_string.get<std::string>();
//	// retrieve the string value (alternative when an variable already exists)
//	std::string cpp_string2;
//	j_string.get_to(cpp_string2);
//
//	// retrieve the serialized value (explicit JSON serialization)
//	std::string serialized_string = j_string.dump();
//
//	// output of original string
//	std::cout << cpp_string << " == " << cpp_string2 << " == " << j_string.get<std::string>() << '\n';
//	// output of serialized value
//	std::cout << j_string << " == " << serialized_string << std::endl;
//}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
