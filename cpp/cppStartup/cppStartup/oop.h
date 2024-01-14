#pragma once

using namespace std;

#include<string>
#include<iostream>
#include<memory>


namespace example1 {
	class Base1 {
	};

	class Derived1 : public Base1 {
	public:
		int var;
	};

	class Base2 {
	};

	class Derived2 : public Base2 {
	public:
		int var;
	};


	/// <summary>
	/// an example of internal pair struct.
	/// </summary>
	/// <typeparam name="T1"></typeparam>
	/// <typeparam name="T2"></typeparam>
	template <class T1, class T2>
	struct pair
	{
		typedef T1 firstType;
		typedef T2 secondType;

		T1 first;
		T2 second;

		pair(): first(T1()), second(T2()){}
		pair(const T1& a, const T2& b) : first(a), second(b) {}

		template <class U1, class U2> 
		pair(const pair<U1, U2>& p) : first(p.first), second(p.second) {}

	};
	
	void test_member_template() {
		cout << "test_member_template()" << endl;
		//implicit convert.
		pair<Derived1, Derived2> p;
		pair<Base1, Base2> p2(pair<Derived1, Derived2>());
		pair<Base1, Base2> p3(p);
		
		Base1* ptr = new Derived1;
		//upcast  
		shared_ptr<Base1> sptr(new Derived1);

	}

}


#include<string>
#include<iostream>
#include<list>
namespace example2 {
	template<typename T, template <typename T> class Container> 
	class XCls {
	private:
		Container<T> c;
	public:
		XCls() {
			for (long i = 0; i < 100; i++) {
				c.insert(c.end(), T() );
			}
		}
	};

	template<typename T>
	using Lst = list<T, allocator<T>>;
	void testTT_param() {
		XCls<string, Lst> mylist;
	}

}

#include<string>
#include<iostream>
#include<memory>
namespace example3 {
	template<typename T, template <typename T> class SmartPtr>
	class XCls {
	private:
		SmartPtr<T> sp;
	public:
		XCls() : sp(new T) {}
	};

	void testTT_param() {
		XCls<string, shared_ptr> p1;
		XCls<double, auto_ptr> p1;
	}
}


#include<iostream>
namespace example5 {
	/// <summary>
	/// this is a demo about auto conversion.
	/// </summary>
	class Fraction {
	public:
		explicit Fraction(int num, int den = 1) :m_numerator(num), m_denominator(den) {
			cout << m_numerator << ' ' << m_denominator << endl; 
		}

		operator double() const {
			return (double)m_numerator / m_denominator;
		}

		Fraction operator+(const Fraction& f) {
			cout << f.m_numerator << f.m_denominator << endl;
			return f;
		}
	private:
		int m_numerator;
		int m_denominator;

	};

	void test_conversion() {
		Fraction f(4, 6);
		double d = 5 + f;
		cout << d;

		//Fraction d2 = f + 4; // f(->double) + 4 ->double can not be converted to Fraction
	}

}
