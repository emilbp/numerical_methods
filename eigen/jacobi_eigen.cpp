#include <armadillo>
#include <cmath>

using namespace arma;

int jacobi_eigen(mat& A, mat& V, vec& e) {
int n = A.n_cols, runs = 0, r1, c1, r2, c2;
bool not_converged = true;
e = A.diag();
V.eye();

while(not_converged){
not_converged = false;

for (int q = 0; q<n; q++) {		// q sweeps the columns
	for (int p = 0; p<q; p++) {	// p sweeps the rows
		double app = e(p);
		double aqq = e(q);
		double apq = A(p,q);
		double phi = atan2(2*apq, aqq-app)/2;
		double c = cos(phi), s = sin(phi);
		double app_new = c*c*app - 2*s*c*apq + s*s*aqq;
		double aqq_new = s*s*app + 2*s*c*apq + c*c*aqq;
		runs++;
		// Limit criterion - if the value changed, update the entry in the matrix
		if (app_new != app || aqq_new != aqq) {
			not_converged = true;
			e(p) = app_new;
			e(q) = aqq_new;
			A(p,q) = 0;

			for (int i = 0; i < n; i++) {
				if (i != q && i != p) {
					if (i < p) {r1 = i; c1 = p;} else {r1 = p; c1 = i;}
					if (i < q) {r2 = i; c2 = q;} else {r2 = q; c2 = i;}

				double aip = A(r1, c1);
				double aiq = A(r2, c2);
				A(r1, c1) = c*aip - s*aiq;
				A(r2, c2) = c*aiq + s * aip;
			}

			double vip = V(i,p);
			double viq = V(i,q);
			V(i,p) = c*vip - s*viq;
			V(i,q) = c*viq + s*vip;

			}
		}
	}

}

}

return runs;
}
