#include <iostream>
#include <cmath>
#include <functional>
#include <armadillo>
using namespace std;
using namespace arma;

tuple<double, double> mc(function<double(vec)> f, vec a, vec b, int N);

int main() {
	function<double(vec)> f1 = [] (vec p) {
		double x = p[0], y = p[1];
		if (x < 1 && y < 1) {
			return 1.0;
		} else {return 0.0;}
	};
	function<double(vec)> f2 = [] (vec p) {
		double x = p[0], y = p[1], z = p[2];
		if (x*x + y*y < 1 && z > 0) {
			return z*2;
		} else {return 0.0;}
	};
	function<double(vec)> f3 = [] (vec p) {
		double x = p[0], y = p[1], z = p[2];
		return 1 / ((1 - cos(x)*cos(y)*cos(z))*M_PI*M_PI*M_PI);
	};

	vec a = {0, 0}, b = {1, 1};
	double ans = 1.0;
	int N = 10000;

	double Q, E;
	tie(Q, E) = mc(f1, a, b, N);

	cout << "Plain Monte Carlo integration of function: z = 1 if (x < 1 and y < 1)" << endl;
	cout << "For x, y from 0 to 1" << endl;
	cout << "Number of sampling points: " << N << endl;
	cout << "Integral: " << Q << endl;
	cout << "Exact ans: " << ans << endl;
	cout << "Est. error: " << E << endl;
	cout << "Actual error: " << abs(Q-ans) << endl << endl;

	a = {-1, -1, 0}, b = {1, 1, 1};
	ans = M_PI;
	N = 100000;

	tie(Q, E) = mc(f2, a, b, N);

	cout << "Plain Monte Carlo integration of function: z = 2z if (x^2 + y^2 < 1 and z > 0)" << endl;
	cout << "For x = {-1, -1, 0} to {1, 1, 1}" << endl;
	cout << "Number of sampling points: " << N << endl;
	cout << "Integral: " << Q << endl;
	cout << "Exact ans: " << ans << endl;
	cout << "Est. error: " << E << endl;
	cout << "Actual error: " << abs(Q-ans) << endl << endl;


	a = {0, 0, 0}, b = {M_PI, M_PI, M_PI};
	ans = 1.3932039296856768591842462603255;
	N = 100000;

	tie(Q, E) = mc(f3, a, b, N);

	cout << "Plain Monte Carlo integration of function:" << endl;
	cout << "1 / (1 - cos(x)*cos(y)*cos(z)) / pi^3" << endl;
	cout << "For x = {0, 0, 0} to {pi, pi, pi}" << endl;
	cout << "Number of sampling points: " << N << endl;
	cout << "Integral: " << Q << endl;
	cout << "Exact ans: " << ans << endl;
	cout << "Est. error: " << E << endl;
	cout << "Actual error: " << abs(Q-ans) << endl << endl;
return 0;
}
