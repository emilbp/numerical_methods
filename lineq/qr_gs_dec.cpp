#include <armadillo>
using namespace arma;

void qr_gs_dec(mat& A, mat& R) {

int m = A.n_cols;

for(int i = 0; i < m; i++) {
	double r = sqrt(dot(A.col(i), A.col(i)));
	R(i,i) = r;
	A.col(i) /= r;
	for(int j = i + 1; j < m; j++) {
		R(i,j) = dot(A.col(i), A.col(j));
		A.col(j) -= A.col(i)*R(i,j);
	}
}


}
