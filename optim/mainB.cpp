#include <iostream>
#include <armadillo>

using namespace arma;
using namespace std;

int quasi_newton(function<double(vec)> f, vec& x0, double eps);

int main() {
	int ncalls = 0;
	vec x(2); x[0] = 0; x[1] = 0;
	vec dx(2); dx[0]=1e-4; dx[1] = 1e-4;
	double tol = 1e-6;

	function<double(vec)> fR = [&ncalls] (vec p) {
		ncalls++;
		double x=p[0],y=p[1];
		double z = (1-x)*(1-x) + 100*(y-x*x)*(y-x*x);
		return z;
	};
	function<double(vec)> fH = [&ncalls] (vec p) {
		ncalls++;
		double x=p[0],y=p[1];
		double z = (x*x + y - 11) * (x*x + y - 11) + (x + y*y - 7)*(x + y*y - 7);
		return z;
	};

	cout << "### Minimum of Rosenbrock's valley function" << endl;
	x.print("x0 = ");
	cout << "f(x0) = " << fR(x) << endl;
	int steps = quasi_newton(fR, x, tol);
	x.print("Minimum found at = ");
	cout << "f(" << x[0] << ", " << x[1] << ") = " << fR(x) << endl;;
	cout << "Minimum found in " << steps << " steps" << endl << endl;


	x[0] = 0; x[1] = 0;
	cout << "### Minimum of Himmelblau's function" << endl;
	x.print("x0 = ");
	cout << "f(x0) = " << fH(x) << endl;
	steps = quasi_newton(fH, x, tol);
	x.print("Minimum found at = ");
	cout << "f(" << x[0] << ", " << x[1] << ") = " << fH(x) << endl;;
	cout << "Minimum found in " << steps << " steps" << endl << endl;



return 0;
}
