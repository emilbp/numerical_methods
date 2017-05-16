#include <cmath>
#include <armadillo>

using namespace std;
using namespace arma;

tuple<double, double> mc(function<double(vec)> f, vec a, vec b, int N) {
	double V = 1; // Volume
	int n = a.size();

	for (int i = 0; i < n; i++) {
		V *= b[i] - a[i];
	}

	double sum1 = 0, sum2 = 0; // to compute integral and variance

	for (int i = 0; i < N; i++) {
		vec x = a + randu(n)%(b-a);
		double fx = f(x);
		sum1 += fx;
		sum2 += fx*fx;
	}

double mean = sum1 / N;
double err = sqrt(sum2 / N - mean*mean) * V / sqrt(N);

return make_tuple(mean*V, err);

}
