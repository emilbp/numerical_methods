#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int jacobi_eigen(mat&, mat&, vec&);
int jacobi_eigen_VbV(mat&, mat&, vec&, int = 0, bool = false);

int main() {
arma_rng::set_seed_random(); // Choose new random alues each time
int n = 50;

mat A = symmatu(randu(n,n)); // Random symmetric matrix
mat V = mat(n,n);
vec e = vec(n);

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

cout << "A is a " << n << "x" << n << " symmetric matrix" << endl;
if (n <= 5) B.print();
cout << endl << "Number of rotations (cyclic sweep): " << sweep_runs << endl;
cout << "Number of rotations (value by value): " << vbv_runs << endl;
cout << "Number of rotations for lowest EV: " << vbv_runs_first << endl;

if (n <= 5) {
(sweep_V.t()*B*sweep_V).print("\nDiagonalization by cyclic sweeps:");
sweep_e.t().print("\nEVs by cyclic sweeps:");
(vbv_V.t()*B*vbv_V).print("\nDiagonalization value by value:");
vbv_e.t().print("\nEVs by cyclic sweeps:");
}
return 0;
}
