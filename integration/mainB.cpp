#include <iostream>
#include <cmath>
#include <functional>
using namespace std;

double adapt_openB(function<double(double)> f, double a, double b, double eps, double acc);

int main() {
int ncalls = 0;
	function<double(double)> f1 = [&ncalls] (double x) {
		ncalls++;
		return exp(-x *x);
	};
	function<double(double)> f2 = [&ncalls] (double x) {
		ncalls++;
		return (1/(pow(x,10)+x));
	};
	function<double(double)> f3 = [&ncalls] (double x) {
		ncalls++;
		return x*exp(x);
	};

	double a = -INFINITY, b = INFINITY, acc = 1e-5, eps = 1e-5;

	string func = "exp(-x * x)"; double ans = sqrt(4*atan(1.0));
	cout << "### Open adaptive integration" << endl;
	cout << "eps = " << eps << ", acc = " << acc << endl << endl;

	double Qo = adapt_openB(f1, a, b, eps, acc);

	cout << "Integrating\t" << func << " from " << a << " to " << b << endl;
	cout << "Exact answer:\t" << ans << endl;
	cout << "Integral:\t" << Qo << endl;
	cout << "Number of f calls: " << ncalls << endl;
	cout << "Est. error:\t" << acc + abs(Qo)*eps << endl;
	cout << "Actual error:\t" << abs(Qo - ans) << endl << endl;

	ncalls = 0; a = 1, b = INFINITY;
	Qo = adapt_openB(f2, a, b, eps, acc);
	func = "1/(x^10 + x)"; ans = log(2)/9;
	cout << "Integrating\t" << func << " from " << a << " to " << b << endl;
	cout << "Exact answer:\t" << ans << endl;
	cout << "Integral:\t" << Qo << endl;
	cout << "Number of f calls: " << ncalls << endl;
	cout << "Est. error:\t" << acc + abs(Qo)*eps << endl;
	cout << "Actual error:\t" << abs(Qo - ans) << endl << endl;

	ncalls = 0; a = -INFINITY, b = -1;
	Qo = adapt_openB(f3, a, b, eps, acc);
	func = "x*exp(x)"; ans = -2/exp(1);
	cout << "Integrating\t" << func << " from " << a << " to " << b << endl;
	cout << "Exact answer:\t" << ans << endl;
	cout << "Integral:\t" << Qo << endl;
	cout << "Number of f calls: " << ncalls << endl;
	cout << "Est. error:\t" << acc + abs(Qo)*eps << endl;
	cout << "Actual error:\t" << abs(Qo - ans) << endl << endl;

return 0;
}
