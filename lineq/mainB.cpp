#include <iostream>
#include <armadillo>
//#include <ctime>

using namespace std;
using namespace arma;

void qr_gs_dec(mat&, mat&);
void qr_gs_inverse(mat&, mat&, mat&);

int main() {
arma_rng::set_seed_random(); // Choose new random values each time

int m = 3;

mat A = randu(m, m);
mat A_save = A;
mat R = zeros(m, m);

cout << "### Calculate inverse of matrix" << endl;
A.print("Random matrix A: ");
qr_gs_dec(A,R);
// From here A is Q, and R is upper triangular

mat B = zeros(m, m);
qr_gs_inverse(A, R, B);

B.print("\nB = A^-1:");
(A_save*B).print("\nCheck: AB = I");
return 0;
}
