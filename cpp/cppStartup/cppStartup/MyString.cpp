#include "MyString.h"

#include <cstring>

// copy cstring
 MyString::MyString(const char* cstr) {
	if (cstr) {
		m_data = new char[strlen(cstr) + 1];
		strcpy_s(m_data,strlen(cstr) + 1, cstr);
	}
	else {
		m_data = new char[1];
		m_data[0] = '\0';
	}
}
char* MyString::get_c_str() const {
	return m_data;
}
// copy MyString
MyString::MyString(const MyString& str) {
	m_data = new char[strlen(str.m_data) + 1];
	strcpy_s(m_data, strlen(str.m_data) + 1, str.m_data);
}

 MyString& MyString::operator = (const MyString& str) {
	// if equals return to prevent delete itself; 
	if (this == &str) {
		return *this;
	}

	delete[] m_data;
	m_data = new char[strlen(str.m_data) + 1];
	strcpy_s(m_data, strlen(str.m_data) + 1, str.m_data);
	return *this;

}

MyString::~MyString() {
	delete[] m_data;
}

#include<iostream>
using namespace std;

std::ostream& operator<<(std::ostream& outs, const MyString& str) {
	outs << str.get_c_str();
	return outs;
}