#include <armadillo>

using namespace arma;
using namespace std;

void qr_gs_dec(mat&, mat&);
void qr_gs_solve(mat&, mat&, vec&);

vec newton(function<vec(vec)> f, vec x0, vec dx, double eps) {
	vec x = x0;
	int n = x.size();
	mat J = zeros(n,n);
	mat R = zeros(n,n);
	vec fx(n), df(n), y(n), fy(n), Dx(n);

	do{
	fx = f(x);
	for (int k = 0; k < n; k++) {
		x[k] += dx[k];
		df = f(x) - fx;
		for (int i = 0; i < n; i++) {
			J(i,k) = df[i] / dx[k];
		}
		x[k] -= dx[k];
	}

	qr_gs_dec(J,R);
		vec minusfx = fx*(-1);
	qr_gs_solve(J,R,minusfx);
		Dx = minusfx;
	double lambda = 2;
	do {
		lambda /=2;
		y = x + Dx * lambda;
		fy = f(y);
	} while(norm(fy,2) > (1-lambda/2)*norm(fx,2) && lambda > 0.02);
	x = y; fx = fy;
	}while(norm(Dx,2) > norm(dx,2) && norm(fx,2) > eps);

return x;
}
