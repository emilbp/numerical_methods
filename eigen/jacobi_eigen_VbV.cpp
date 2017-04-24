#include <armadillo>
#include <cmath>

using namespace arma;

int jacobi_eigen_VbV(mat& A, mat& V, vec& e, int eigenvals, bool reverse) {
int n = A.n_cols, runs = 0, r1, c1, r2, c2, es;

e = A.diag();
V.eye();

if (eigenvals == 0) {es = n;} else {es = eigenvals+1;}

vec converged = zeros(es);

for (int h = 0; h < es-1; h++) {
int p = h;
while(converged(h) == 0){

for (int q = p+1; q<n; q++) {		// q sweeps the columns
// p sweeps the rows
		double app = e(p);
		double aqq = e(q);
		double apq = A(p,q);
		double phi = atan2(2*apq, aqq-app)/2;
		if (reverse == true) {phi += 3.14159265358979323846/2;}
		double c = cos(phi), s = sin(phi);
		double app_new = c*c*app - 2*s*c*apq + s*s*aqq;
		double aqq_new = s*s*app + 2*s*c*apq + c*c*aqq;

		// Limit criterion - if the value changed, update the entry in the matrix
		if (app_new != app || aqq_new != aqq) {
			runs++;
			converged(h) = 0;
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
		} else {converged(h) = 1;}
	}


}
}
return runs;
}
