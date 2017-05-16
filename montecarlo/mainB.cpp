#include <iostream>
#include <cmath>
#include <functional>
#include <armadillo>
using namespace std;
using namespace arma;

tuple<double, double> mc(function<double(vec)> f, vec a, vec b, int N);

int main() {
	function<double(vec)> f2 = [] (vec p) {
		double x = p[0], y = p[1], z = p[2];
		if (x*x + y*y < 1 && z > 0) {
			return z*2;
		} else {return 0.0;}
	};

	vec a = {-1, -1, 0}, b = {1, 1, 1};
	double ans = M_PI;
	int N;

	vec Ns(100), As(100), Es(100);
	for (int i = 0; i < 100; i++) {
		N = (i+1) * 1000;
		double Q, E;
		tie(Q,E) = mc(f2, a, b, N);
		As(i) = abs(Q-ans), Es(i) = E, Ns(i) = N;
	}

	cout << "\"Actual error\" \"Estimated error\" \"Expected behavior O(1/sqrt(N))\"";
	for (int i = 0; i < 100; i++) {
		cout << Ns(i) << " " << As(i) << " " << Es(i) << " " << exp(1)/sqrt(Ns(i)) << endl;
	}
return 0;
}
