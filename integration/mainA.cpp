#include <iostream>
#include <cmath>
#include <functional>
using namespace std;

double adapt_open(function<double(double, int)> f, int p, double a, double b, double eps, double acc);
double adapt_closed(function<double(double, int)> f, int p, double a, double b, double eps, double acc);

int main() {
int ncalls = 0;
	function<double(double, int)> f = [&ncalls] (double x, int p) {
		ncalls++;
		switch(p) {
			case 1:
				return sqrt(x);
			case 2:
				return 1/sqrt(x);
			case 3:
				return log(x)/sqrt(x);
			case 4:
				return 4*sqrt(1 - (1-x)*(1-x));
			default:
				throw invalid_argument("Function not defined");
		}
	};

	double a = 0, b = 1, acc = 1e-5, eps = 1e-5;
	int p = 1;

	double Q1 = adapt_open(f, p, a, b, eps, acc);
	double Q2 = adapt_closed(f, p, a, b, eps, acc);

	cout << "Q is: " << Q1 << endl;
	cout << "Q is: " << Q2 << endl;
	cout << "Number of f calls: " << ncalls << endl;
return 0;
}
