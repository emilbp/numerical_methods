#include <functional>
#include <cmath>
#include <iostream>
#include <complex>

using namespace std;
typedef complex<double> dcomp;

dcomp integ(function<dcomp(dcomp)> f, dcomp a, dcomp b, dcomp f1, dcomp f3, dcomp f5, double acc, double eps);

dcomp adapt(function<dcomp(dcomp)> f, dcomp a, dcomp b, double acc, double eps) {
	dcomp f1 = f(a);
	dcomp f3 = f((a+b)/2.);
	dcomp f5 = f(b);
	return integ(f, a, b, f1, f3, f5, acc, eps);
}

dcomp integ(function<dcomp(dcomp)> f, dcomp a, dcomp b, dcomp f1, dcomp f3, dcomp f5, double acc, double eps) {
	dcomp f2 = f(a + (b-a)/4.);
	dcomp f4 = f(a + 3.*(b-a)/4.);

	dcomp Q = ((f1 + f5)/8. + (f2 + f3 + f4)/4.) * (b-a);
	dcomp q = ((f1 + f5)/4. + f3/2.) * (b-a);

	double tol = acc + (abs(Q)*eps);
	double err = abs(abs(Q)-abs(q))/2.;

	if (err < tol) {
		return Q;
	} else {
		acc /= sqrt(2);
		return(integ(f, a, (a+b)/2., f1, f2, f3, acc, eps) + integ(f, (a+b)/2., b, f3, f4, f5, acc, eps));
	}
}
