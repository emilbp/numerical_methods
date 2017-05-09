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
		dydx[0] = -y[1];
		dydx[1] = y[0];
		return dydx;
	};

	vector<double> xlist(1), xlist2(1), xlist3(1);
	vector<vec> ylist(1),ylist2(1),ylist3(1);
	double pi = 3.14159265358979323846;
	double a = 0, b = 3, h = 0.1, acc = 0.01, eps = 0.01;


	xlist[0] = a; ylist[0] = vec({0,10});
	rkdriver(f1, xlist, ylist, "ode12", b, h, acc, eps);

	cout << "\"ode12: y1\" \"ode12: y2\"" << endl;
	for(int i=0;i<xlist.size();i++) {
		cout << xlist[i] << " " << ylist[i][0] << " " << ylist[i][1] << endl;
	}

	xlist2[0] = a; ylist2[0] = vec({0,10});
	rkdriver(f1, xlist2, ylist2, "ode23", b, h, acc, eps);

	cout << endl << endl << "\"ode23: y1\" \"ode23: y2\"" << endl;
	for(int i=0;i<xlist2.size();i++) {
		cout << xlist2[i] << " " << ylist2[i][0] << " " << ylist2[i][1] << endl;
	}

	xlist3[0] = a; ylist3[0] = vec({0,10});
	rkdriver(f1, xlist3, ylist3, "ode45", b, h, acc, eps);

	cout << endl << endl << "\"ode45: y1\" \"ode45: y2\"" << endl;
	for(int i=0;i<xlist3.size();i++) {
		cout << xlist3[i] << " " << ylist3[i][0] << " " << ylist3[i][1] << endl;
	}


return 0;
}
