#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int jacobi_eigen_VbV(mat&, mat&, vec&, int, bool = false);

int main() {
arma_rng::set_seed_random(); // Choose new random alues each time
int n = 4;

mat A = symmatu(randu(n,n)); // Random symmetric matrix
mat V = mat(n,n);
vec e = vec(n);

A.print("A is a random symmetric matrix:");
mat B = A; // Keep a copy of A
int runs = jacobi_eigen_VbV(A, V, e, 0); // Computes all eigenvalue. If another integer is supplied as last argument, that number of EVs are calculated

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


return 0;
}
