#include <iostream>
#include <complex>
#include <cmath>
#include <functional>

using namespace std;
typedef complex<double> dcomp;

main() {
	dcomp i = -1; i = sqrt(i);
	double pi = 2 * asin(1);

	dcomp a = exp(2*pi*i);
	cout << "i is " << i << " and Euler was right: e(i pi) = " << a << endl;

	a = 2. + 2.*i;
	dcomp b = 1. + 0.5*i;
	cout << "a is " << a << endl;
	cout << "b is " << b << endl;
	cout << "a*b is " << a*b << endl;

	function<dcomp(dcomp)> f = [] (dcomp z) {
		return 2.*z;
	};

	cout << endl << "a is " << a << endl;
	cout << "b is " << b << endl;
	cout << "f(a) is " << f(a) << endl;
	cout << "f(a)*b is " << f(a)*b << endl;
	cout << "b*conj(b) is " << b*conj(b) << endl;
}
