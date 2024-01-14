
#ifndef Complex
#define Complex

class complex {
public:
	complex(double r = 0, double i = 0);

	complex& operator += (const complex& r);

	complex& operator -= (const complex& r);

	complex& operator *= (const complex& r);


	double real() const {
		return re;
	}

	double imag() const {
		return im;
	}

private:
	double re, im;

	friend complex& __doami(complex*, const complex&);

	friend complex& __doaml(complex*, const complex&);

	friend complex& __doapl(complex*, const complex&);

};


extern inline double real(const complex& x);

extern inline double imag(const complex& x);

extern complex& __doapl(complex* ths, const complex& r);

extern complex& __doami(complex* ths, const complex& r);

extern complex& __doaml(complex* ths, const complex& r);


extern inline complex operator + (const complex& x, double y);
extern inline complex operator + (const complex& x, const complex& y);
extern inline complex operator + (double x, const complex& y);
extern inline complex operator + (const complex& x);
extern inline complex operator - (const complex& x, const complex& y);
extern inline complex operator - (const complex& x, double y);
extern inline complex operator - (double x, const complex& y);
extern inline complex operator - (const complex& x);
extern inline complex operator * (const complex& x, double y);
extern inline complex operator * (double y, const complex& x);
extern inline complex operator * (const complex& x, const complex& y);
extern inline complex operator / (const complex& x, double y);
extern inline complex polar(double, double);
extern inline complex conj(const complex& x);
extern inline double norm(const complex& x);
extern inline bool operator == (const complex& x, const complex& y);
extern inline bool operator == (const complex& x, double y);
extern inline bool operator == (double x, const complex& y);
extern inline bool operator != (const complex& x, const complex& y);
extern inline bool operator != (double x, const complex& y);
extern inline bool operator != (const complex& x, double y);


# endif

