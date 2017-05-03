#include <iostream>
#include <armadillo>

using namespace arma;
using namespace std;

vec newton(function<vec(vec)> f, vec x0, vec dx, double eps);

int main() {
	int ncalls = 0;
	vec x(2); x[0]=2; x[1]=1;
	vec dx(2); dx[0]=1e-6; dx[1] = 1e-6;

	function<vec(vec)> fA1 = [&ncalls] (vec p) {
		ncalls++;
		vec z(2); double x=p[0],y=p[1];
		z[0] = 10000*x*y - 1;
		z[1] = exp(-x) + exp(-y) - 1 - 1/10000;
		return z;
	};
	function<vec(vec)> fA2 = [&ncalls] (vec p) {
		ncalls++;
		vec z(2); double x=p[0],y=p[1];
		z[0] = 2*(200*x*x*x - 200*x*y + x + 1);
		z[1] = 200*(y - x*x);
		return z;
	};
	function<vec(vec)> fA3 = [&ncalls] (vec p) {
		ncalls++;
		vec z(2); double x=p[0],y=p[1];
		z[0] = 2*(2*x*(x*x + y - 11) + x + y*y - 7);
		z[1] = 2*(x*x + 2*y*(x + y*y - 7) + y - 11);
		return z;
	};

	cout << "Solve the system: Axy=1; exp(-x) + exp(-y) = 1 + 1/A; A=10000" << endl;
	x.print("Initial vector x0:");
	fA1(x).print("f(x0):");

	ncalls = 0;
	vec b = newton(fA1, x, dx, 1e-6);
	int ncalls_final = ncalls;

	b.print("\nSolution x:");
	fA1(b).print("f(x):");
	cout << endl << "Number of function calls: " << ncalls_final << endl << endl;

	x[0]=2; x[1]=1;
	dx[0]=1e-6; dx[1] = 1e-6;

	cout << "Minimum of Rosenbrock's valley function" << endl;
	x.print("Initial vector x0:");
	fA2(x).print("f(x0):");
	ncalls = 0;
	b = newton(fA2, x, dx, 1e-6);
	ncalls_final = ncalls;
	b.print("\nSolution x:");
	fA2(b).print("f(x):");
	cout << endl << "Number of function calls: " << ncalls_final << endl << endl;


	x[0]=2; x[1]=1;
	dx[0]=1e-6; dx[1] = 1e-6;
	cout << "Minimum of Himmelblau's function" << endl;
	x.print("Initial vector x0:");
	fA3(x).print("f(x0):");
	ncalls = 0;
	b = newton(fA3, x, dx, 1e-6);
	ncalls_final = ncalls;
	b.print("\nSolution x:");
	fA3(b).print("f(x):");
	cout << endl << "Number of function calls: " << ncalls_final << endl << endl;

return 0;
}
