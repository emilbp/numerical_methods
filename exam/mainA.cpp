#include <iostream>
#include <complex>
#include <cmath>
#include <functional>

using namespace std;
typedef complex<double> dcomp;

dcomp adapt(function<dcomp(dcomp)> f, dcomp a, dcomp b, double acc, double eps);

main() {
	dcomp i = -1; i = sqrt(i);
	double pi = 2 * asin(1), acc = 1e-5, eps = 1e-5;

	function<dcomp(dcomp)> f = [] (dcomp z) {
		return z;
	};
	function<dcomp(dcomp)> f2 = [] (dcomp z) {
		return z*z;
	};

	dcomp a = 0. + 0.*i, b = 1. + i, res;

	res = adapt(f2, a, b, acc, eps);

	cout << "Res is: " << res << endl;


/*
	dcomp a = 2. + 2.*i;
	dcomp b = 1. + 0.5*i;
	cout << "a is " << a << endl;
	cout << "b is " << b << endl;
	cout << "a*b is " << a*b << endl;
	cout << endl << "a is " << a << endl;
	cout << "b is " << b << endl;
	cout << "f(a) is " << f2(a) << endl;
	cout << "f(a)*b is " << f2(a)*b << endl;
	cout << "b*conj(b) is " << b*conj(b) << endl;
*/
}
