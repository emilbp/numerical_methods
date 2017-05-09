#include <iostream>
#include <cmath>
#include <functional>
using namespace std;

double adapt(function<double(double)> f, double a, double b, double eps, double acc);

int main() {
int ncalls = 0;
	function<double(double)> f = [&ncalls] (double x) {
		ncalls++;
		return 4 * sqrt(1 - (1-x)*(1-x));
	};

	double a = 0, b = 1, acc = 1e-5, eps = 1e-5;

	double Q = adapt(f, a, b, eps, acc);

	cout << "f(0.5) is: " << f(0.5) << endl;
	cout << "Q is: " << Q << endl;
	cout << "Number of f calls: " << ncalls << endl;
return 0;
}
