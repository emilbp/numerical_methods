#include <armadillo>
#include <cmath>

using namespace arma;

int jacobi_eigen(mat& A, mat& V, vec& e) {
int n = A.n_cols, sweeps = 0;
bool changed = true;
e = A.diag();
V.eye();

while(changed){
sweeps++;

for (int q = n-1; q>0; q--) {		// q sweeps the columns
	for (int p = 0; p<q; p++) {	// p sweeps the rows
		double app = e(p);
		double aqq = e(q);
		double apq = A(p,q);
		double phi = atan2(2*apq, aqq-app)/2;
		double c = cos(phi), s = sin(phi);
		double app_new = c*c*app - 2*s*c*apq + s*s*aqq;
		double aqq_new = s*s*app + 2*s*c*apq + c*c*aqq;

		// Limit criterion - if the value changed, update the entry in the matrix
		if (app_new != app || aqq_new != aqq) {
			changed = true;
			e(p) = app_new;
			e(q) = aqq_new;
			A(p,q) = 0.0;

			for (int i = 0; i<p; i++) {
				double aip = A(i,p);
				double aiq = A(i,q);
				A(i,p) = c*aip - s*aiq;
				A(i,q) = s*aip + c*aiq;
			}
			for (int i = p+1; i<q; i++) {
				double api = A(p,i);
				double aiq = A(i,q);
				A(p,i) = c*api - s*aiq;
				A(i,q) = c*aiq + s*api;
			}
			for (int i = q+1; i<n; i++) {
				double api = A(p,i);
				double aqi = A(q,i);
				A(p,i) = c*api - s*aqi;
				A(q,i) = c*aqi + s*api;
			}
			for (int i = 0; i<n; i++) {
				double vip = V(i,p);
				double viq = V(i,q);
				V(i,p) = c*vip - s*viq;
				V(i,q) = s*vip + c*viq;
			}
		} else { changed = false; }
	}

}

}

return sweeps;
}
