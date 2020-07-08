#include <iostream>
#include "parse/json11.hpp"
#include <string>
#include "codec/gbk_utf8.hpp"

using namespace std;

int main()
{
	const string simple_test =
		R"({"k1":"v1", "k2":42, "k3":["a",123,true,false,null]})";

	string err;
	const auto json = roco::Json::parse(simple_test, err);

	std::cout << "k1: " << json["k1"].string_value() << "\n";
	std::cout << "k2: " << json["k2"].int_value() << endl;
	std::cout << "k3: " << json["k3"].dump() << "\n";

	for (auto& k : json["k3"].array_items()) {
		std::cout << "    - " << k.dump() << "\n";
	}
}