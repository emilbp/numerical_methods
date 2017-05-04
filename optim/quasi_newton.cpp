#include <armadillo>

using namespace arma;
using namespace std;

vec gradient(function<double(vec)> f, vec x, double dx) {
	double fx = f(x);
	int n = x.size();
	vec dfdx = zeros(n);
	for (int i = 0; i < n; i++) {
		x[i] += dx;
		dfdx[i] = (f(x) - fx) / dx;
		x[i] -= dx;
	}
	return dfdx;
}

int quasi_newton(function<double(vec)> f, vec& x, double eps) {
	int steps = 0;
	int n = x.size();
	vec Dx(n), y(n), dfdx_n(n), xn(n), s(n);
	double fx = f(x), dx = 1e-6;
	vec dfdx = gradient(f, x, dx);
	mat Hi = eye(n,n);

	do {
		Dx = -Hi * dfdx;

		double lambda = 2;
		do {
			lambda /= 2;
			s = Dx * lambda;
			if (norm(s,2) < dx) Hi = eye(n,n);
		}while(abs(f(x + s)) > abs(fx) + 0.01 * lambda * dot(Dx.t(), dfdx) && norm(s,2) > dx);

	// Take the step lambda * Dx and update values at new x
	xn = x + s;
	dfdx_n = gradient(f, xn, dx);
	y = dfdx_n - dfdx;

	Hi += (s-Hi*y)*(s.t()*Hi)/dot(y.t(), (Hi*s)); // Calculate the updated Hessian

	x = xn;
	fx = f(x);
	dfdx = dfdx_n;
	steps++;
	}while(norm(dfdx,2) > eps); // Converges when the gradient is zero

return steps;
}


