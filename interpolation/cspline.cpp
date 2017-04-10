#include <functional>
#include <vector>
#include <stdexcept>
#include <cmath>
#include <iostream>
using namespace std;

function<double(double, int)> cspline(vector<double>&x, vector<double>&y) {
//if(y.size() != x.size()) throw logic_error("x.size != y.size");

int n = x.size();
vector<double> p(n-1), dx(n-1), b(n), c(n-1), d(n-1), D(n), Q(n-1), B(n);

for (int i = 0; i < n-1; i++) {
	dx[i] = x[i+1] - x[i];
	p[i] = (y[i+1] - y[i]) / dx[i];
}

D[0] = 2; Q[0] = 1; B[0] = 3*p[0]; D[n-1] = 2; B[n-1] = 3*p[n-2];

for (int i = 0; i < n-2; i++) {
	D[i+1] = 2 * dx[i] / dx[i+1] + 2;
	Q[i+1] = dx[i] / dx[i+1];
	B[i+1] = 3*(p[i] + p[i+1] * dx[i] / dx[i+1]);
}

for (int i = 1; i < n; i++) {
	D[i] = D[i] - Q[i-1] / D[i-1];
	B[i] = B[i] - B[i-1] / D[i-1];
}

b[n-1] = B[n-1] / D[n-1];

for (int i = n-2; i >= 0; i--) {
	b[i] = (B[i] - Q[i] * b[i+1]) / D[i];
}

for (int i = 0; i < n-1; i++) {
	c[i] = (-2 * b[i] - b[i+1] + 3 * p[i]) / dx[i];
	d[i] = (b[i] + b[i+1] - 2 * p[i]) / pow(dx[i],2);
}

return [x,y,n,b,c,d](double z, int flag = 0)->double {

	int i = 0, j = n - 1;

	while(j - i > 1) {
		int m = (i + j) / 2;
		if(z > x[m]) {
			i = m;
		}
		else {
			j = m;
		}
	};

	double dx = z - x[i];
	switch(flag) {
	case 0: { // Return cspline
		return y[i] + dx * b[i] + c[i] * pow(dx, 2) + d[i] * pow(dx, 3);
	}
	case 1: { // Return integral
		double S = 0;
		for (int k = 0; k<i; k++) {
			double dx = x[k+1] - x[k];
			S += dx*(y[k] + dx*(b[k]/2 + dx*(c[k]/3 + dx*d[k]/4)));
		}
		return S + dx*(y[i] + dx*(b[i]/2 + dx*(c[i]/3 + dx*d[i]/4)));
	}
	case -1: { // Return derivative
		return b[i] + 2*c[i]*dx + 3*d[i]*pow(dx,2);
	}
	default: {cerr << "cspline: wrong flag: " << flag << endl; return NAN;}
	}
};
}
