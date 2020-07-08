#pragma once

#ifndef _ROCO_PARSE_TINYXML2_EX_HPP_
#define _ROCO_PARSE_TINYXML2_EX_HPP_

#include <Windows.h>

#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "../roco_ns.h"
#include "tinyxml2.hpp"
#include "../assert/assert_any.hpp"
#include "../codec/code_converter.hpp"

_ROCO_BEGIN

/**
* @brief 
*/
class Tinyxml2_ex
{
public:
	using Element_type = XMLElement*;

	Tinyxml2_ex() = default;

	Tinyxml2_ex(std::string xml_file, bool utf8_code = false) noexcept
	{
		doc_ = new XMLDocument();
		//std::ifstream infile(xml_file,
		//	std::ios::ios_base::in | std::ios::basic_ios::binary);
		//std::ostringstream oss;
		//oss << infile.rdbuf();
		//ready_ = (XML_SUCCESS == doc_->LoadFile(xml_file.c_str()));
		parse_file_(xml_file, utf8_code);
	}

	~Tinyxml2_ex() noexcept
	{
		try
		{
			if (doc_ != nullptr)
				delete doc_;
		}
		catch (...)
		{
		}
	}

	Tinyxml2_ex(const Tinyxml2_ex&) = delete;
	Tinyxml2_ex(Tinyxml2_ex&&) = delete;
	Tinyxml2_ex& operator = (const Tinyxml2_ex&) = delete;
	Tinyxml2_ex& operator = (Tinyxml2_ex&&) = delete;

public:
	bool parse_file(std::string xml_file, bool utf8_code = false)
	{
		reset_xml_document_();
		//ready_ = (XML_SUCCESS == doc_->LoadFile(xml_file.c_str()));
		parse_file_(xml_file, utf8_code);
		return ready_;
	}

	bool parse_text(std::string const& xml_text, bool utf8_code = false)
	{
		reset_xml_document_();
		parse_text_(xml_text, utf8_code);
		return ready_;
	}

	Element_type root()
	{
		ASSERT_ANY(ready_);
		return doc_->RootElement();
	}

	bool has_ancestry(Element_type ele, char const* ancestry)
	{
		auto p_node = ele->Parent();
		while (true)
		{
			if (::strcmp(ancestry, p_node->ToElement()->Name()) == 0)
				return true;

			if (p_node->ToElement() == root()) return false;
			p_node = p_node->Parent();
		}
		return false;
	}

public:
	std::vector<Element_type> all(const char* ele_name) 
	{
		ASSERT_ANY(ready_);
		vec_.clear();
		all_(ele_name, root());
		return vec_;
	}

	std::vector<Element_type> all(const char* ele_name, const char* parent) 
	{
		ASSERT_ANY(ready_);
		vec_.clear();
		all_(ele_name, root(), parent);
		return vec_;
	}

	std::vector<Element_type> all(const char* ele_name, const char* parent, const char* pparent) 
	{
		ASSERT_ANY(ready_);
		vec_.clear();
		all_(ele_name, root(), parent, pparent);
		return vec_;
	}

	std::vector<Element_type> childs(Element_type ele, char const* child_name = nullptr) const
	{
		std::vector<Element_type> v;
		if (ele->NoChildren())
			return v;

		Element_type n = ele->FirstChildElement(child_name);
		while (n)
		{
			v.push_back(n);
			n = n->NextSiblingElement(child_name);
		}
		return v;
	}

	Element_type parent(Element_type ele) const
	{
		return ele->Parent()->ToElement();
	}

public:
	std::string text(Element_type ele) const
	{
		return ele->GetText();
	}

	//std::wstring text_w(Element_type ele) 
	//{
	//	return trans_wchar_(ele->GetText());
	//}

	//std::string text_from_utf8(Element_type ele)
	//{
	//	std::string t = text(ele);
	//	return Code_converter::utf8_to_ansi(t);
	//}

	std::pair<bool, int32_t> int32_attribute(Element_type ele, char const* attr_name) 
	{
		int32_t value;
		auto result = ele->QueryIntAttribute(attr_name, &value);
		return std::make_pair(result == XML_SUCCESS, value);
	}

	std::pair<bool, std::string> string_attribute(Element_type ele, char const* attr_name) 
	{
		auto v = ele->Attribute(attr_name);
		return std::make_pair(v != NULL, v == NULL ? "" : v);
	}

	//std::pair<bool, std::wstring> wstring_attribute(Element_type ele, const char* attr_name) 
	//{
	//	auto v = ele->Attribute(attr_name);
	//	return std::make_pair(v != NULL, v == NULL ? std::wstring() : trans_wchar_(v));
	//}

	//std::pair<bool, std::string> string_attribute_from_utf8(Element_type ele, char const* attr_name)
	//{
	//	auto v = ele->Attribute(attr_name);
	//	if (v == NULL)
	//		return std::make_pair(false, "");

	//	std::string s(v);
	//	return std::make_pair(true, Code_converter::utf8_to_ansi(s));
	//}

	std::pair<bool, bool> bool_attribute(Element_type ele, char const* attr_name) 
	{
		bool value;
		auto result = ele->QueryBoolAttribute(attr_name, &value);
		return std::make_pair(result == XML_SUCCESS, value);
	}

	std::pair<bool, double> double_attribute(Element_type ele, char const* attr_name) 
	{
		double value;
		auto result = ele->QueryDoubleAttribute(attr_name, &value);
		return std::make_pair(result == XML_SUCCESS, value);
	}

public:
	bool ready() const
	{
		return ready_;
	}

private:
	void all_(const char* name, Element_type ele)
	{
		if (::strcmp(name, ele->Name()) == 0) {
			vec_.push_back(ele);
		}
		if (ele->FirstChildElement()) {
			all_(name, ele->FirstChildElement());
		}
		if (ele->NextSiblingElement()) {
			all_(name, ele->NextSiblingElement());
		}
	}

	void all_(const char* name, Element_type ele, const char* parent)
	{
		if (::strcmp(name, ele->Name()) == 0) {
			if (ele->Parent() &&
				(::strcmp(parent, ele->Parent()->ToElement()->Name()) == 0))
				vec_.push_back(ele);
		}
		if (ele->FirstChildElement()) {
			all_(name, ele->FirstChildElement(), parent);
		}
		if (ele->NextSiblingElement()) {
			all_(name, ele->NextSiblingElement(), parent);
		}
	}

	void all_(const char* name, Element_type ele, const char* parent, const char* pparent)
	{
		if (::strcmp(name, ele->Name()) == 0) {
			if (ele->Parent() &&
				(::strcmp(parent, ele->Parent()->ToElement()->Name()) == 0))
				if (ele->Parent()->Parent() &&
					(::strcmp(pparent, ele->Parent()->Parent()->ToElement()->Name()) == 0))
					vec_.push_back(ele);
		}
		if (ele->FirstChildElement()) {
			all_(name, ele->FirstChildElement(), parent, pparent);
		}
		if (ele->NextSiblingElement()) {
			all_(name, ele->NextSiblingElement(), parent, pparent);
		}
	}

	//std::wstring trans_wchar_(const char* s)
	//{
	//	int buf_len = ::MultiByteToWideChar(CP_UTF8, 0, s, -1, nullptr, 0);
	//	if (buf_len == 0) return std::wstring();

	//	wchar_t* buf = new wchar_t[buf_len];
	//	int ret = ::MultiByteToWideChar(CP_UTF8, 0, s, -1, buf, buf_len);
	//	if (ret == 0) return std::wstring();

	//	std::wstring ws(buf);
	//	delete[] buf;
	//	return ws;
	//}

	void reset_xml_document_()
	{
		try
		{
			if (doc_ != nullptr)
				delete doc_;
		}
		catch (...)
		{
		}
		doc_ = new XMLDocument();
	}

	void parse_text_(std::string const& s, bool utf8_code)
	{
		if (utf8_code)
		{
			std::string s_ansi = Code_converter::utf8_to_ansi(s);
			ready_ = (XML_SUCCESS == doc_->Parse(s_ansi.c_str()));
		}
		else
		{
			ready_ = (XML_SUCCESS == doc_->Parse(s.c_str()));
		}
	}

	void parse_file_(std::string const& file, bool utf8_code)
	{
		std::ifstream infile(file,
			std::ios::ios_base::in | std::ios::basic_ios::binary);
		std::ostringstream oss;
		oss << infile.rdbuf();
		parse_text_(oss.str(), utf8_code);
	}

private:
	std::vector<Element_type> vec_;

private:
	XMLDocument* doc_{ nullptr };
	bool ready_{ false };
};

_ROCO_END

#endif // _ROCO_PARSE_TINYXML2_EX_HPP_
