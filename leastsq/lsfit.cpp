#include <armadillo>
using namespace arma;

void qr_gs_dec(mat&, mat&);
void qr_gs_solve(mat&, mat&, vec&);
void qr_gs_inverse(mat &, mat&, mat&);
void inverse(mat &, mat&);

void lsfit(vec& x, vec& y, vec& dy, const std::vector<std::function<double(double)>> & funs, vec & c, mat & S) {
int n = x.size(), m = funs.size();

mat A(n,m), R(m,m);
vec b = y/dy;
for (int i = 0; i < n; i++) {
	for (int k = 0; k < m; k++) {
		A(i,k) = funs[k](x[i])/dy[i];
	}
}

mat A_save = A;
qr_gs_dec(A,R);

qr_gs_solve(A, R, b);
c = b;

mat Ri = zeros(m,m);
inverse(R, Ri);

S = Ri*Ri.t();
}

void inverse(mat& A, mat& B) {
int n = A.n_rows;
mat R = mat(n,n);
qr_gs_dec(A,R);
vec b = zeros(n);
vec x = vec(n);
for (int i = 0; i<n; i++) {
	b(i) = 1.0;
	qr_gs_solve(A, R, b);
	x = b;
	b(i) = 0.0;
	B.col(i) = x;
}
}
