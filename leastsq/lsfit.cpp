#include <armadillo>
using namespace arma;

void qr_gs_dec(mat&, mat&);
void qr_gs_solve(mat&, mat&, vec&);
void qr_gs_inverse(mat &, mat&, mat&);

void lsfit(vec& x, vec& y, vec& dy, const std::vector<std::function<double(double)>> & funs, vec & c, mat & S) {
int n = x.size(), m = funs.size();

// Setup the matrix A for solving the system
mat A(n,m), R(m,m);
vec b = y/dy;
for (int i = 0; i < n; i++) {
	for (int k = 0; k < m; k++) {
		A(i,k) = funs[k](x[i])/dy[i];
	}
}

// Solve the system by QR-decomposition and back substitution
qr_gs_dec(A,R);
qr_gs_solve(A, R, b);
c = b;

// Calculate the covariance matrix
mat Ri = zeros(m,m);
mat R_new = mat(m,m);
qr_gs_dec(R, R_new);
qr_gs_inverse(R, R_new, Ri);
S = Ri*Ri.t();
}
