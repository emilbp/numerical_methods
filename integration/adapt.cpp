#include <functional>
#include <cmath>
#include <iostream>
using namespace std;

double integ_open(function<double(double, int)> f, int p, double a, double b, double f2, double f3, double acc, double eps);
double integ_closed(function<double(double, int)> f, int p, double a, double b, double f1, double f3, double f5, double acc, double eps);

double adapt_open(function<double(double, int)> f, int p, double a, double b, double acc, double eps) {
	double f2 = f(a + 2*(b-a)/6, p);
	double f3 = f(a + 4*(b-a)/6, p);
	return integ_open(f, p, a, b, f2, f3, acc, eps);
}

double integ_open(function<double(double, int)> f, int p, double a, double b, double f2, double f3, double acc, double eps) {
	double f1 = f(a + (b-a)/6, p);
	double f4 = f(a + 5*(b-a)/6, p);
	double Q = (2*f1 + f2 + f3 + 2*f4)*(b-a)/6;
	double q = (f1 + f2 + f3 + f4) * (b-a) / 4;
	double tol = acc + abs(Q)*eps;
	double err = abs(Q-q)/2;

	if (err < tol) {
		return Q;
	} else {
		acc /= sqrt(2);
		return (integ_open(f, p, a, (a+b)/2, f1, f2, acc, eps) + integ_open(f, p, (a+b)/2, b, f3, f4, acc, eps));
	}
}

double adapt_closed(function<double(double, int)> f, int p, double a, double b, double acc, double eps) {
	double f1 = f(a, p);
	double f3 = f((a+b)/2, p);
	double f5 = f(b, p);
	return integ_closed(f, p, a, b, f1, f3, f5, acc, eps);
}

double integ_closed(function<double(double, int)> f, int p, double a, double b, double f1, double f3, double f5, double acc, double eps) {
	double f2 = f(a + (b-a)/4, p);
	double f4 = f(a + 3*(b-a)/4, p);
	double Q = ((f1 + f5)/8 + (f2 + f3 + f4)/4)*(b-a);
	double q = ((f1 + f5)/4 + f3/2)*(b-a);
	double tol = acc + abs(Q)*eps;
	double err = abs(Q-q)/2;

	if (err < tol) {
		return Q;
	} else {
		acc /= sqrt(2);
		return (integ_closed(f, p, a, (a+b)/2, f1, f2, f3, acc, eps) + integ_closed(f, p, (a+b)/2, b, f3, f4, f5, acc, eps));
	}
}
