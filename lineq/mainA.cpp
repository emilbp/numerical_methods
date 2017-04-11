#include <iostream>
#include <armadillo>
//#include <ctime>

using namespace std;
using namespace arma;

void qr_gs_dec(mat&, mat&);
void qr_gs_solve(mat&, mat&, vec&);

int main() {
arma_rng::set_seed_random(); // Choose new random values each time

int n = 4, m = 3;

mat A = randu(n, m);
mat R = zeros(m, m);

A.print("Random matrix A: ");
qr_gs_dec(A,R);

A.print("\nMatrix Q:");
R.print("\nMatrix R: (should be upper triangular)");

(A.t()*A).print("\nQ^TQ: (should be equal to 1)");

(A*R).print("\nQR: (should be equal to A)");


// Linear systems
cout << "\n\n### Linear equation" << endl;
cout << "Ax = b, solve for x" << endl;
A = randu(m, m);
mat A_save = A; // Save a copy of A, for later check

A.print("\nA:");
vec b = randu(m);
b.print("\nVector b:");

R = zeros(m, m);
qr_gs_dec(A,R);
cout << "\nQR-decomposition results:" << endl;
A.print("\nQ:");
R.print("\nR:");


qr_gs_solve(A,R,b);
b.print("\n\nSolution x:");
(A_save*b).print("\nAx: (Should be equal to b)");

return 0;
}
