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
				break;
			case 2:
				return 1/sqrt(x);
				break;
			case 3:
				return log(x)/sqrt(x);
				break;
			case 4:
				return 4*sqrt(1 - (1-x)*(1-x));
				break;
			default:
				throw invalid_argument("Function not defined");
		}
	};

	double a = 0, b = 1, acc = 1e-5, eps = 1e-5;

	cout << "### Open adaptive integration" << endl;
	cout << "eps = " << eps << ", acc = " << acc << endl << endl;
	for (int i = 1; i < 5;) {
	double ans; int no; string func;
	switch(i) {
		case 1:
			func = "sqrt(x)"; ans = 2.0/3.0;
			break;
		case 2:
			func = "1/sqrt(x)"; ans = 2;
			break;
		case 3:
			func = "ln(x)/sqrt(x)"; ans = -4;
			break;
		case 4:
			func = "4*sqrt(1 - (1-x)^2)"; ans = 4*atan(1.0);
			break;
	}
	ncalls = 0;
	double Qo = adapt_open(f, i, a, b, eps, acc);
	no = ncalls; ncalls = 0;
	cout << "Integrating\t" << func << " from " << a << " to " << b << endl;
	cout << "Exact answer:\t" << ans << endl;
	cout << "Integral:\t" << Qo << endl;
	cout << "Number of f calls: " << no << endl;
	cout << "Est. error:\t" << acc + abs(Qo)*eps << endl;
	cout << "Actual error:\t" << abs(Qo - ans) << endl << endl;
	i++;
	}

	cout << endl << "### Closed adaptive integration" << endl;
	cout << "eps = " << eps << ", acc = " << acc << endl << endl;
	ncalls = 0;
	double Qc = adapt_closed(f, 4, a, b, eps, acc);
	cout << "Integrating\t 4*sqrt(1 - (1-x)^2)" << " from " << a << " to " << b << endl;
	cout << "Exact answer:\t" << 4*atan(1.0) << endl;
	cout << "Integral:\t" << Qc << endl;
	cout << "Number of f calls: " << ncalls << endl;
	cout << "Est. error:\t" << acc + abs(Qc)*eps << endl;
	cout << "Actual error:\t" << abs(Qc - 4*atan(1.0)) << endl << endl;

return 0;
}
