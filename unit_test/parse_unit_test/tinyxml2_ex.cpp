#include "pch.h"
#include "CppUnitTest.h"
#include "parse/tinyxml2_ex.hpp"
#include "extension/sstream.hpp"
#include <fstream>
#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace roco;
using namespace std;

namespace parseunittest
{
	TEST_CLASS(Tinyxml2_ex_unittest)
	{
	public:

		TEST_METHOD(load_file_test)
		{
			Tinyxml2_ex tiny("test_ansi.xml");
			Assert::IsTrue(tiny.ready());

			Tinyxml2_ex tiny2("test_utf8.xml", true);
			Assert::IsTrue(tiny2.ready());

			Tinyxml2_ex tiny3("test_bomutf8.xml", true);
			Assert::IsTrue(tiny3.ready());

			//Tinyxml2_ex tiny4("test_bombuni.xml");
			//Assert::IsFalse(tiny4.ready());

			//Tinyxml2_ex tiny5("test_bomluni.xml");
			//Assert::IsFalse(tiny5.ready());

			tiny2.parse_file("test_ansi.xml");
			Assert::IsTrue(tiny2.ready());

			tiny2.parse_file("test_utf8.xml", true);
			Assert::IsTrue(tiny2.ready());

			tiny3.parse_file("test_bomutf8.xml", true);
			Assert::IsTrue(tiny3.ready());
		}

		TEST_METHOD(parse_text)
		{
			/**
			 * test_ansi.xml
			 */
			ifstream infile("test_ansi.xml", 
				ios::ios_base::in | ios::basic_ios::binary);
			ostringstream oss;
			oss << infile.rdbuf();

			Tinyxml2_ex tiny;
			tiny.parse_text(oss.str());
			Assert::IsTrue(tiny.ready());

			/**
			 * test_utf8.xml
			 */
			infile.close();
			infile.open("test_utf8.xml",
				ios::ios_base::in | ios::basic_ios::binary);
			clear_content(oss) << infile.rdbuf();
			tiny.parse_text(oss.str());
			Assert::IsTrue(tiny.ready());

			/**
			 * test_bomutf8.xml
			 */
			infile.close();
			infile.open("test_bomutf8.xml",
				ios::ios_base::in);
			clear_content(oss) << infile.rdbuf();
			tiny.parse_text(oss.str().c_str());
			Assert::IsTrue(tiny.ready());

			/**
			 * test_bombuni.xml
			 */
			//infile.close();
			//infile.open("test_bombuni.xml",
			//	ios::ios_base::in);
			//clear_content(oss) << infile.rdbuf();
			//tiny.parse_text(oss.str().c_str());
			//Assert::IsFalse(tiny.ready());

			/**
			 * test_bomluni.xml
			 */
			//infile.close();
			//infile.open("test_bomluni.xml",
			//	ios::ios_base::in);
			//clear_content(oss) << infile.rdbuf();
			//tiny.parse_text(oss.str().c_str());
			//Assert::IsFalse(tiny.ready());
		}

		TEST_METHOD(root_test)
		{
			Tinyxml2_ex tiny("test_ansi.xml");
			Assert::IsTrue(tiny.ready());
			Assert::IsNotNull(tiny.root());

			tiny.parse_file("test_utf8.xml", true);
			Assert::IsTrue(tiny.ready());
			Assert::IsNotNull(tiny.root());

			tiny.parse_file("test_bomutf8.xml");
			Assert::IsTrue(tiny.ready());
			Assert::IsNotNull(tiny.root());
		}

		TEST_METHOD(has_ancestry_test)
		{
			Tinyxml2_ex tiny("test_ansi.xml");
			Assert::IsTrue(tiny.ready());

			auto v = tiny.all("ID1");
			Assert::AreEqual((size_t)1, v.size());
			Assert::IsTrue(tiny.has_ancestry(v[0], "CORE_ID"));

			v = tiny.all("ID2");
			Assert::AreEqual((size_t)1, v.size());
			Assert::IsTrue(tiny.has_ancestry(v[0], "CORE_ID"));

			v = tiny.all("ID3");
			Assert::AreEqual((size_t)1, v.size());
			Assert::IsTrue(tiny.has_ancestry(v[0], "CORE_ID"));

			v = tiny.all("ID");
			Assert::AreEqual((size_t)13, v.size());
			Assert::IsTrue(tiny.has_ancestry(v[12], "CORE_ID"));
			Assert::IsFalse(tiny.has_ancestry(v[10], "Hello"));

			tiny.parse_file("test_utf8.xml", true);
			Assert::IsTrue(tiny.ready());

			v = tiny.all("ID1");
			Assert::AreEqual((size_t)1, v.size());
			Assert::IsTrue(tiny.has_ancestry(v[0], "CORE_ID"));

			v = tiny.all("ID2");
			Assert::AreEqual((size_t)1, v.size());
			Assert::IsTrue(tiny.has_ancestry(v[0], "CORE_ID"));

			v = tiny.all("ID3");
			Assert::AreEqual((size_t)1, v.size());
			Assert::IsTrue(tiny.has_ancestry(v[0], "CORE_ID"));

			v = tiny.all("ID");
			Assert::AreEqual((size_t)13, v.size());
			Assert::IsTrue(tiny.has_ancestry(v[12], "CORE_ID"));
			Assert::IsFalse(tiny.has_ancestry(v[10], "Hello"));

			tiny.parse_file("test_bomutf8.xml");
			Assert::IsTrue(tiny.ready());

			v = tiny.all("ID1");
			Assert::AreEqual((size_t)1, v.size());
			Assert::IsTrue(tiny.has_ancestry(v[0], "CORE_ID"));

			v = tiny.all("ID2");
			Assert::AreEqual((size_t)1, v.size());
			Assert::IsTrue(tiny.has_ancestry(v[0], "CORE_ID"));

			v = tiny.all("ID3");
			Assert::AreEqual((size_t)1, v.size());
			Assert::IsTrue(tiny.has_ancestry(v[0], "CORE_ID"));

			v = tiny.all("ID");
			Assert::AreEqual((size_t)13, v.size());
			Assert::IsTrue(tiny.has_ancestry(v[12], "CORE_ID"));
			Assert::IsFalse(tiny.has_ancestry(v[10], "Hello"));
		}

		TEST_METHOD(attribute_test)
		{
			/**
			 * test_ansi.xml
			 */
			Tinyxml2_ex tiny("test_ansi.xml");
			Assert::IsTrue(tiny.ready());

			auto v = tiny.all("ID1");
			Assert::AreEqual((size_t)1, v.size());
			auto p = tiny.string_attribute(v[0], "DESC");
			Assert::IsTrue(p.first);
			Assert::IsTrue(p.second == std::string("VDR域"));
			
			v = tiny.all("ID2");
			Assert::AreEqual((size_t)1, v.size());
			p = tiny.string_attribute(v[0], "DESC");
			Assert::IsTrue(p.first);
			Assert::IsTrue(p.second == std::string("VDR ID"));

			v = tiny.all("ID3");
			Assert::AreEqual((size_t)1, v.size());
			p = tiny.string_attribute(v[0], "DESC");
			Assert::IsTrue(p.first);
			Assert::IsTrue(p.second == std::string("运行控制指令"));

			/**
			 * test_utf8.xml
			 */
			tiny.parse_file("test_utf8.xml", true);
			Assert::IsTrue(tiny.ready());

			v = tiny.all("ID1");
			Assert::AreEqual((size_t)1, v.size());
			auto p2 = tiny.string_attribute(v[0], "DESC");
			Assert::IsTrue(p2.first);
			Assert::IsTrue(p2.second == std::string("VDR域"));
			auto p3 = tiny.string_attribute(v[0], "DESC");
			Assert::IsTrue(p3.first);
			Assert::IsTrue(p3.second == std::string("VDR域"));

			v = tiny.all("ID2");
			Assert::AreEqual((size_t)1, v.size());
			p = tiny.string_attribute(v[0], "DESC");
			Assert::IsTrue(p.first);
			Assert::IsTrue(p.second == std::string("VDR ID"));
			p2 = tiny.string_attribute(v[0], "DESC");
			Assert::IsTrue(p2.first);
			Assert::IsTrue(p2.second == std::string("VDR ID"));
			p3 = tiny.string_attribute(v[0], "DESC");
			Assert::IsTrue(p3.first);
			Assert::IsTrue(p3.second == std::string("VDR ID"));

			v = tiny.all("ID3");
			Assert::AreEqual((size_t)1, v.size());
			p2 = tiny.string_attribute(v[0], "DESC");
			Assert::IsTrue(p2.first);
			Assert::IsTrue(p2.second == std::string("运行控制指令"));
			p3 = tiny.string_attribute(v[0], "DESC");
			Assert::IsTrue(p3.first);
			Assert::IsTrue(p3.second == std::string("运行控制指令"));

			/**
			 * test_bomutf8.xml
			 */
			tiny.parse_file("test_bomutf8.xml", true);
			Assert::IsTrue(tiny.ready());

			v = tiny.all("ID1");
			Assert::AreEqual((size_t)1, v.size());
			p2 = tiny.string_attribute(v[0], "DESC");
			Assert::IsTrue(p2.first);
			Assert::IsTrue(p2.second == std::string("VDR域"));
			p3 = tiny.string_attribute(v[0], "DESC");
			Assert::IsTrue(p3.first);
			Assert::IsTrue(p3.second == std::string("VDR域"));

			v = tiny.all("ID2");
			Assert::AreEqual((size_t)1, v.size());
			p = tiny.string_attribute(v[0], "DESC");
			Assert::IsTrue(p.first);
			Assert::IsTrue(p.second == std::string("VDR ID"));
			p2 = tiny.string_attribute(v[0], "DESC");
			Assert::IsTrue(p2.first);
			Assert::IsTrue(p2.second == std::string("VDR ID"));
			p3 = tiny.string_attribute(v[0], "DESC");
			Assert::IsTrue(p3.first);
			Assert::IsTrue(p3.second == std::string("VDR ID"));

			v = tiny.all("ID3");
			Assert::AreEqual((size_t)1, v.size());
			p2 = tiny.string_attribute(v[0], "DESC");
			Assert::IsTrue(p2.first);
			Assert::IsTrue(p2.second == std::string("运行控制指令"));
			p3 = tiny.string_attribute(v[0], "DESC");
			Assert::IsTrue(p3.first);
			Assert::IsTrue(p3.second == std::string("运行控制指令"));
		}
	};
}