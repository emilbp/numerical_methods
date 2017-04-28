#include <armadillo>
using namespace arma;

void qr_gs_dec(mat&, mat&);
void qr_gs_solve(mat&, mat&, vec&);
void qr_gs_inverse(mat &, mat&, mat&);

void lsfit(vec& x, vec& y, vec& dy, const std::vector<std::function<double(double)>> & funs, vec & c, mat & S) {
int n = x.size(), m = funs.size();

mat A(n,m), R(m,m);
vec b = y/dy;
for (int i = 0; i < n; i++) {
	for (int k = 0; k < m; k++) {
		A(i,k) = funs[k](x[i])/dy[i];
	}
}

qr_gs_dec(A,R);

qr_gs_solve(A, R, b);

mat Ri(m,m);
qr_gs_inverse(R, R, Ri);

S = Ri*Ri.t();
c = b;
}
