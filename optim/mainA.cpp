#include <iostream>
#include <armadillo>

using namespace arma;
using namespace std;

int newton_mini(function<double(vec)> f, function<vec(vec)> g, function<mat(vec)> H, vec& x0, double eps);

int main() {
	int ncalls = 0;
	vec x(2); x[0] = -4; x[1] = -4;
	vec dx(2); dx[0]=1e-4; dx[1] = 1e-4;
	double tol = 1e-8;

	function<double(vec)> fR = [&ncalls] (vec p) {
		ncalls++;
		double x=p[0],y=p[1];
		double z = (1-x)*(1-x) + 100*(y-x*x)*(y-x*x);
		return z;
	};
	function<vec(vec)> gfR = [&ncalls] (vec p) {
		ncalls ++;
		vec z(2); double x=p[0],y=p[1];
		z[0] = 2*x - 400*x*(y-x*x) - 2;
		z[1] = 200*y - 200*x*x;
		return z;
	};
	function<mat(vec)> HfR = [&ncalls] (vec p) {
		ncalls++;
		mat z(2,2); double x=p[0],y=p[1];
		z(0,0) = 1200*x*x - 400*y + 2;
		z(1,0) = -400*x;
		z(0,1) = -400*x;
		z(1,1) = 200;
		return z;
	};
	function<double(vec)> fH = [&ncalls] (vec p) {
		ncalls++;
		double x=p[0],y=p[1];
		double z = (x*x + y - 11) * (x*x + y - 11) + (x + y*y - 7)*(x + y*y - 7);
		return z;
	};
	function<vec(vec)> gfH = [&ncalls] (vec p) {
		ncalls ++;
		vec z(2); double x=p[0],y=p[1];
		z[0] = 4*x*x*x + 4*x*y - 42*x + 2*y*y - 14;
		z[1] = 2*x*x + 4*x*y + 4*y*y*y - 26*y - 22;
		return z;
	};
	function<mat(vec)> HfH = [&ncalls] (vec p) {
		ncalls++;
		mat z(2,2); double x=p[0],y=p[1];
		z(0,0) = 12*x*x + 2*(2*y - 21);
		z(1,0) = 4*x + 4*y;
		z(0,1) = 4*x + 4*y;
		z(1,1) = 12*y*y + 2*(2*x - 13);
		return z;
	};

	cout << "### Minimum of Rosenbrock's valley function" << endl;
	x.print("x0 = ");
	cout << "f(x0) = " << fR(x) << endl;
	int steps = newton_mini(fR, gfR, HfR, x, tol);
	x.print("Minimum found at = ");
	cout << "f(" << x[0] << ", " << x[1] << ") = " << fR(x) << endl;;
	cout << "Minimum found in " << steps << " steps" << endl << endl;


	x[0] = -4; x[1] = -4;
	cout << "### Minimum of Himmelblau's function" << endl;
	x.print("x0 = ");
	cout << "f(x0) = " << fH(x) << endl;
	steps = newton_mini(fH, gfH, HfH, x, tol);
	x.print("Minimum found at = ");
	cout << "f(" << x[0] << ", " << x[1] << ") = " << fH(x) << endl;;
	cout << "Minimum found in " << steps << " steps" << endl;



return 0;
}
