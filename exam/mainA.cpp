#include <iostream>
#include <complex>
#include <cmath>
#include <functional>

using namespace std;
typedef complex<double> dcomp;

dcomp adapt(function<dcomp(dcomp)> f, dcomp a, dcomp b, double acc, double eps);

main() {
	dcomp i = -1; i = sqrt(i);
	double pi = 2 * asin(1);

	// Define integration tolerance
	double acc = 1e-5, eps = 1e-5;

	// Define functions to integrate
	function<dcomp(dcomp)> f = [] (dcomp z) {
		return z;
	};
	function<dcomp(dcomp)> f2 = [] (dcomp z) {
		return z*z;
	};
	function<dcomp(dcomp)> f3 = [] (dcomp z) {
		return 1./z;
	};
	function<dcomp(dcomp)> f4 = [] (dcomp z) {
		return exp(z);
	};

	cout << "#####################\n# Numerical methods #\n#  Exam project 20  #\n# Emil T. Bjerglund #\n#####################" << endl;

	cout << endl << "Adaptive integration of complex functions" << endl << endl;

	// Define endpoints (a,b) of a line in the complex plane to integrate over
	dcomp a = 1. + i, b = 3. + 3.*i;
	dcomp res;
	res = adapt(f, a, b, acc, eps);
	cout << "f1(z) = z" << endl;
	cout << "a = " << real(a) << "+" << imag(a) << "i" << ", b = " << real(b) << "+" << imag(b) << "i" << endl;
	cout << "Integral of f1 from a to b = " << real(res) << " + " << imag(res) << "i" << endl << endl;

	a = 0. + 0.*i, b = 1. + 1.*i;
	res = adapt(f2, a, b, acc, eps);
	cout << "f2(z) = z^2" << endl;
	cout << "a = " << real(a) << "+" << imag(a) << "i" << ", b = " << real(b) << "+" << imag(b) << "i" << endl;
	cout << "Integral of f2 from a to b = " << real(res) << " + " << imag(res) << "i" << endl << endl;

	a = 1. + 0.*i, b = 2. - 1.*i;
	res = adapt(f3, a, b, acc, eps);
	cout << "f3(z) = 1/z" << endl;
	cout << "a = " << real(a) << "+" << imag(a) << "i" << ", b = " << real(b) << "+" << imag(b) << "i" << endl;
	cout << "Integral of f3 from a to b = " << real(res) << " + " << imag(res) << "i" << endl << endl;

	a = 0. + 0.*i, b = 1. + 1.*i;
	res = adapt(f4, a, b, acc, eps);
	cout << "f4(z) = e^z" << endl;
	cout << "a = " << real(a) << "+" << imag(a) << "i" << ", b = " << real(b) << "+" << imag(b) << "i" << endl;
	cout << "Integral of f4 from a to b = " << real(res) << " + " << imag(res) << "i" << endl << endl;
}
