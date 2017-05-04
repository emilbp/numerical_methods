#include <armadillo>

using namespace arma;
using namespace std;

void qr_gs_dec(mat&, mat&);
void qr_gs_solve(mat&, mat&, vec&);

int newton_mini(function<double(vec)> f, function<vec(vec)> g, function<mat(vec)> hes, vec& x, double eps) {
	int steps = 0;
	int n = x.size();
	vec Dx(n);
	mat R(n,n);
	double fx = f(x);
	vec dfdx = g(x);
	mat H = hes(x);

	do {
		qr_gs_dec(H,R);
			vec minusgx = dfdx*(-1);
		qr_gs_solve(H,R,minusgx);
			Dx = minusgx;

		double lambda = 2;
		do {
			lambda /= 2;
		}while(f(x + lambda * Dx) > fx + 0.0001*lambda*dot(Dx.t(),dfdx) && lambda > 0.02);
	// Take the step lambda * Dx and update values at new x
	x += lambda * Dx;
	fx = f(x);
	dfdx = g(x);
	H = hes(x);
	steps++;
	}while(norm(dfdx) > eps); // Converges when the gradient is zero

return steps;
}
