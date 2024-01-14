#ifndef __MYSTRING
#define __MYSTRING

class MyString
{
public:
	MyString(const char* cstr = 0);
	MyString(const MyString& str);
	MyString& operator = (const MyString& str);
	~MyString();
	char* get_c_str() const;
private:
	char* m_data;
};

#include<iostream>
using namespace std;
extern ostream& operator<<(ostream&, const MyString&);



#endif