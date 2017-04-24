#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int jacobi_eigen(mat&, mat&, vec&);
int jacobi_eigen_VbV(mat&, mat&, vec&, int = 0, bool = false);

int main() {
arma_rng::set_seed_random(); // Choose new random alues each time
int n = 5;

mat A = symmatu(randu(n,n)); // Random symmetric matrix
mat V = mat(n,n);
vec e = vec(n);

A.print("A is a random symmetric matrix:");
mat B = A; // Keep a copy of A

int sweep_runs = jacobi_eigen(A, V, e); // Computes all eigenvalue. If another integer is supplied as last argument, that number of EVs are calculated
mat sweep_A = A;
mat sweep_V = V;
vec sweep_e = e;

A = B;
int vbv_runs = jacobi_eigen_VbV(A, V, e);
mat vbv_A = A;
mat vbv_V = V;
vec vbv_e = e;

A = B;
int vbv_runs_first = jacobi_eigen_VbV(A, V, e, 1);

cout << endl << "Number of rotations (cyclic sweep): " << sweep_runs << endl;
cout << "Number of rotations (value by value): " << vbv_runs << endl;
cout << "Number of rotations for first EV: " << vbv_runs_first << endl;
/*



cout << endl << "### Jacobi Eigenvalue Algorithm, Value by Value" << endl;
cout << "Number of runs: " << runs << endl;
(V.t()*B*V).print("\nV^T*A*V (should be diagonal):");
e.t().print("\nEigenvalues (should be equal to diagonal above):");
A.print("\nA after (upper triangle should be zeroed, while the rest is untouched):");

A = B;
runs = jacobi_eigen_VbV(A, V, e, 1);
cout << endl << "First eigenvalue: " << e(0) << endl;
A = B;
runs = jacobi_eigen_VbV(A, V, e, 1, true);
cout << "Last eigenvalue: " << e(0) << endl;
*/

return 0;
}
