#include <iostream>
#include <armadillo>
//#include <ctime>

using namespace std;
using namespace arma;

void qr_gs_dec(mat&, mat&);

int main() {
arma_rng::set_seed_random(); // Choose new random values each time

int n = 4, m = 3;

mat A = randu(n, m);
mat R = zeros(m, m);

A.print("Random matrix A: ");
qr_gs_dec(A,R);

A.print("\nMatrix Q:");
R.print("\nMatrix R: ");

return 0;
}
