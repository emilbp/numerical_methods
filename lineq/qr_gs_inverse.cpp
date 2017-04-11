#include <armadillo>
using namespace arma;

void qr_gs_solve(mat&, mat&, vec&);

void qr_gs_inverse(mat& Q, mat& R, mat& B) {
int m = Q.n_cols;

mat e = eye(m, m); // Create identity matrix

// Solve linear equations for each column to find the inverse
for(int i = 0; i < m; i++) {
	vec b = e.col(i);
	qr_gs_solve(Q, R, b);
	B.col(i) = b;
}

}
