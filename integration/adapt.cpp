#include <functional>
#include <cmath>
#include <iostream>
using namespace std;

double integ_open(function<double(double)> f, double a, double b, double f2, double f3, double acc, double eps);

double adapt(function<double(double)> f, double a, double b, double acc, double eps) {
	double f2 = f(a + (b-a)/3);
	double f3 = f(a + 2*(b-a)/3);
	return integ_open(f, a, b, f2, f3, acc, eps);
}

double integ_open(function<double(double)> f, double a, double b, double f2, double f3, double acc, double eps) {
	double f1 = f(a + (b-a)/6);
	double f4 = f(a + 5*(b-a)/6);
	double Q = (f1 + f4) * (b-a) / 3 + (f2 + f3) * (b-a) / 6;
	double q = (f1 + f2 + f3 + f4) * (b-a) / 4;
	double tol = acc + abs(Q)*eps;
	double err = abs(Q-q)/2;

	if (err < tol) {
		return Q;
	} else {
		acc /= sqrt(2);
		return (integ_open(f, a, (a+b)/2, f1, f2, acc, eps) + integ_open(f, (a+b)/2, b, f3, f4, acc, eps));
	}
}
