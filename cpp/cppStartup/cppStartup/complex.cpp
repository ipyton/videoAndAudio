#include "complex.h"



complex::complex(double r, double i) : re(r), im(i) {

}
inline complex& 
__doami(complex* ths, const complex& r) {
	ths->re -= r.re;
	ths->im -= r.im;
	return *ths;
}

inline complex& 
__doaml(complex* ths, const complex& r) {
	double f = ths->re * r.re - ths->im * r.im;
	ths->im = ths->re * r.im + ths->im * r.re;
	ths->re = f;
	return *ths;
}


inline complex& 
__doapl(complex* ths, const complex& r) {
	ths->re += r.re;
	ths->im += r.im;
	return *ths;
}

complex& 
complex::operator += (const complex& r) {
	return __doapl(this, r);
}

complex& 
complex::operator -= (const complex& r) {
	return __doami(this, r);
}

complex& 
complex::operator *= (const complex& r) {
	return __doaml(this, r);
}



inline double real(const complex& x) {
	return x.real();
}

inline double imag(const complex& x) {
	return x.imag();
}

inline complex operator + (const complex& x, double y) {
	return complex(real(x) + y, imag(x));
}

inline complex operator + (const complex& x, const complex& y) {
	return complex(real(x) + real(y), imag(x) + imag(y));
}

inline complex operator + (double x, const complex& y) {
	return complex(real(y) + x, imag(y));
}

inline complex operator + (const complex& x) {
	return x;
}
 
inline complex operator - (const complex& x, const complex& y) {
	return complex(real(x) - real(y), imag(x) - imag(y));
}

inline complex operator - (const complex& x, double y) {
	return complex(real(x) - y, imag(y) );
}

inline complex operator - (double x, const complex& y) {
	return complex(real(y) - x, imag(y));
}

inline complex operator - (const complex& x) {
	return complex(-real(x), -imag(x));
}

inline complex operator * (const complex& x, double y) {
	return complex(y * real(x), y * imag(x));
}


inline complex operator * (double y, const complex& x) {
	return complex(y * real(x), y * imag(x));
}

inline complex operator * (const complex& x, const complex& y) {
	return complex(real(x) * real(y) - imag(x) * imag(y),
		real(x) * imag(y) + imag(x) + real(y));
}

inline complex operator / (const complex& x, double y) {
	return complex(real(x) / y, imag(x) / y);
}


inline bool operator == (const complex& x, const complex& y) {
	return real(x) == real(y) && imag(x) == imag(y);
}

inline bool operator == (const complex& x, double y) {
	return imag(x) == 0 && real(x) == y;
}

inline bool operator == (double x, const complex& y) {
	return imag(y) == 0 && real(y) == x;
}

inline bool operator != (const complex& x, const complex& y) {
	return real(x) != real(y) || imag(x) != imag(y);
}

inline bool operator != (double x, const complex& y) {
	return imag(y) != 0 || real(y) != x;
}

inline bool operator != (const complex& x, double y) {
	return imag(x) != 0 || real(x) != y;
}

#include<cmath>

//convert the coodinate position to polar position.
inline complex polar(double r, double t) {
	return complex(r * cos(t), r * sin(t));
}


inline complex conj(const complex& x) {
	return complex(real(x), -imag(x));
}

inline double norm(const complex& x) {
	return real(x) * real(x) + imag(x) * imag(x);
}









