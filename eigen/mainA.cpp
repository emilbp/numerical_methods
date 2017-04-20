#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int jacobi_eigen(mat&, mat&, vec&);

int main() {
arma_rng::set_seed_random(); // Choose new random alues each time
int n = 4;

mat A = symmatu(randu(n,n)); // Random symmetric matrix
mat V = mat(n,n);
vec e = vec(n);

A.print("A is a random symmetric matrix:");
mat B = A; // Keep a copy of A
int runs = jacobi_eigen(A, V, e);

cout << endl << "### Jacobi Eigenvalue Algorithm" << endl;
cout << "Number of runs: " << runs << endl;
(V.t()*B*V).print("\nV^T*A*V (should be diagonal):");
e.t().print("\nEigenvalues (should be equal to diagonal above):");
A.print("\nA after (upper triangle should be zeroed, while the rest is untouched):");
return 0;
}
