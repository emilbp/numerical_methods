#include <armadillo>

using namespace arma;
using namespace std;

void qr_gs_dec(mat&, mat&);
void qr_gs_solve(mat&, mat&, vec&);

vec newton_analytic(function<vec(vec)> f, function<mat(mat)> df, vec x0, double eps) {
	vec x = x0;
	int n = x.size();
	mat R = zeros(n,n);
	vec fx(n), y(n), fy(n), Dx(n);
	mat J(n,n);

	do{
	fx = f(x);
	J = df(x);

	// Solve J Dx = -f(x) to find the step-direction and size
	qr_gs_dec(J,R);
		vec minusfx = fx*(-1);
	qr_gs_solve(J,R,minusfx);
		Dx = minusfx;

	// First iteration does full step, and then halves lambda for each step
	double lambda = 2;
	do {
		lambda /=2;
		y = x + Dx * lambda;
		fy = f(y);
	} while(norm(fy,2) > (1-lambda/2)*norm(fx,2) && lambda > 0.02);

	// Take the step and then iterate again until ||f(x)|| < tolerance
	x = y;
	}while(norm(fy,2) > eps);

return x;
}
