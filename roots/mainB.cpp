#include <iostream>
#include <armadillo>

using namespace arma;
using namespace std;

vec newton(function<vec(vec)> f, vec x0, vec dx, double eps);
vec newton_analytic(function<vec(vec)> f, function<mat(mat)> df, vec x0, double eps);

int main() {
	int ncalls = 0;
	vec x(2), x0(2); x0[0] = 2; x0[1] = 1; x = x0;
	vec dx(2); dx[0]=1e-4; dx[1] = 1e-4;
	double tol = 1e-8;

	function<vec(vec)> fA2 = [&ncalls] (vec p) {
		ncalls++;
		vec z(2); double x=p[0],y=p[1];
		z(0) = 2*(200*x*x*x - 200*x*y + x + 1);
		z(1) = 200*(y - x*x);
		return z;
	};
	function<mat(mat)> dfA2 = [&ncalls] (vec p) {
		ncalls++;
		mat z(2,2); double x=p[0],y=p[1];
		z(0,0) = 1200*x*x - 400*y + 2; // dfA2 / dx
		z(1,0) = (-1)*400 * x; // dfA2 / dx
		z(0,1) = (-1)*400 * x; // dfA2 / dx
		z(1,1) = 200; // dfA2 / dy
		return z;
	};

	cout << "Minimum of Rosenbrock's valley function (numeric)" << endl;
	x.print("Initial vector x0:");
	fA2(x).print("f(x0):");
	ncalls = 0;
	vec b = newton(fA2, x, dx, tol);
	int ncalls_numeric = ncalls;
	b.print("\nSolution x:");
	fA2(b).print("f(x):");

	cout << "\nMinimum of Rosenbrock's valley function (analytic jacobian)" << endl;
	x = x0;
	x.print("Initial vector x0:");
	fA2(x).print("f(x) is");
	ncalls = 0;
	vec c = newton_analytic(fA2, dfA2, x, tol);
	int ncalls_analytic = ncalls;
	c.print("Solution x using analytic jacobian:");
	fA2(c).print("f(x):");

	cout << endl << endl << "Number of function calls saved for analytic method: " << ncalls_numeric - ncalls_analytic << endl << endl;
return 0;
}
