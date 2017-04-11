#include <armadillo>
using namespace arma;

void qr_gs_solve(mat& Q, mat& R, vec& b) {
// Need to solve QRx = b by applying Q^T to b in-place, and then performing back-substitution in-place
int m = R.n_rows;
b = Q.t() * b;
// From here, Rx = b. Now we need to find x by back-substitution

for(int i = m-1; i>=0; i--) {

	double sum = 0;
	for(int j = i + 1; j < m; j++) {
		sum += R(i,j)*b(j);
	}
		b(i) = (b(i) - sum)/R(i,i);
}
}

