#include <functional>
#include <vector>
#include <stdexcept>
#include <cmath>
#include <iostream>
using namespace std;

function<double(double, int)> lspline(vector<double>&x, vector<double>&y) {
//if(y.size() != x.size()) throw logic_error("x.size != y.size");


return [x,y](double z, int flag = 0)->double {

	int i = 0, j = x.size() - 1;

	while(j - i > 1) {
		int m = (i + j) / 2;
		if(z > x[m]) {
			i = m;
		}
		else {
			j = m;
		}
	};

	double p = (y[i+1] - y[i]) / (x[i+1] - x[i]);

	switch(flag) {
	case 0: { // Return spline
		return y[i] + p*(z - x[i]);
	}
	case 1: { // Return integral from 0 to z
		double S = 0;
		for (int k = 0; k<i; k++) {
			double h = x[k+1] - x[k];
			S += h*y[k] + 0.5 * p * pow(h, 2);
		}
		return S + (y[i]*(z-x[i]) + 0.5 * p * pow(z-x[i],2));
	}
	default: {cerr << "lspline: wrong flag: " << flag << endl; return NAN;}
	}
};
}
