#include <iostream>
#include <armadillo>

using namespace arma;
using namespace std;

void rkdriver(
	function<vec(double,vec)> & F,
	vector<double> & xlist, vector<vec> & ylist,
	string mode,
	double  b, double h, double acc, double eps);

int main() {
	function<vec(double, vec)> f1 = [] (double x, vec y) {
		int n = y.size(); vec dydx(n);
		dydx[0] = y[1];
		dydx[1] = -y[0];
		return dydx;
	};

	vector<double> xlist(1);
	vector<vec> ylist(1);
	double pi = 3.141592;
	double a = 0, b = 2*pi, h = 0.01, acc = 0.01, eps = 0.01, shift = 0.05;

	xlist[0] = a; ylist[0] = vec({0,1});
	rkdriver(f1, xlist, ylist, "ode12", b, h, acc, eps);

	cout << "\"ode12: y2\" \"ode12: y2\"" << endl;
	for(int i=0;i<xlist.size();i++) {
		cout << xlist[i] << " " << ylist[i][0] << " " << ylist[i][1] << endl;
	}


	xlist[0] = a; ylist[0] = vec({0,1});
	rkdriver(f1, xlist, ylist, "ode32", b, h, acc, eps);

	cout << endl << endl << "\"ode32: y1\" \"ode32: y2\"" << endl;
	for(int i=0;i<xlist.size();i++) {
		cout << xlist[i] << " " << ylist[i][0] - shift << " " << ylist[i][1] - shift << endl;
	}

	xlist[0] = a; ylist[0] = vec({0,1});
	rkdriver(f1, xlist, ylist, "ode45", b, h, acc, eps);

	cout << endl << endl << "\"ode45: y1\" \"ode45: y2\"" << endl;
	for(int i=0;i<xlist.size();i++) {
		cout << xlist[i] << " " << ylist[i][0] + shift << " " << ylist[i][1] + shift << endl;
	}


return 0;
}
