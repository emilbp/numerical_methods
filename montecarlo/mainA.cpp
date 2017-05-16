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

	cout << "Q is: " << Q << endl;
	cout << "E is: " << E << endl;
return 0;
}
