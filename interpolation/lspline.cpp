#include <functional>
#include <vector>
#include <stdexcept>
#include <cmath>
#include <iostream>
using namespace std;

function<double(double, int)> lspline(vector<double>&x, vector<double>&y) {
//if(y.size() != x.size()) throw logic_error("x.size != y.size");

int n = x.size();
vector<double> p(n-1);

for(int i=0; i<n-1; i++) {p[i] = (y[i+1] - y[i]) / (x[i+1] - x[i]);}


return [x,y,p](double z, int flag = 0)->double {

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

	double h = z - x[i];

	switch(flag) {
	case 0: { // Return spline
		return y[i] + p[i]*h;
	}
	case 1: { // Return integral from 0 to z
		double S = 0;
		for (int k = 0; k<i; k++) {
			double h = x[k+1] - x[k];
			S += h*(y[k] + p[k]*h*0.5);
		}
		//return S + y[i]*z + 0.5*p[i]*pow(z,2) - z*p[i]*x[i];
		return S + h*(y[i] + p[i]*h*0.5);
	}
	default: {cerr << "lspline: wrong flag: " << flag << endl; return NAN;}
	}
};
}
