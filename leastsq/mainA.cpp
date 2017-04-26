#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

void qr_gs_dec(mat&, mat&);
void qr_gs_solve(mat&, mat&, vec&);

int main() {
arma_rng::set_seed_random();

vec x, y, dy;
x  = {0.100, 0.145, 0.211, 0.307, 0.447, 0.649, 0.944, 1.372, 1.995, 2.900};
y  = {12.644, 9.235, 7.377, 6.460, 5.555, 5.896, 5.673, 6.964, 8.896, 11.355};
dy = {0.858, 0.359, 0.505, 0.403, 0.683, 0.605, 0.856, 0.351, 1.083, 1.002};
int n = x.size();

for (int i = 0; i < n; i++) {
	cout << "# m=1, S=2\n";
	cout << x[i] <<" "<< y[i]-dy[i] <<"\n";
	cout << x[i] <<" "<< y[i] <<"\n";
	cout << x[i] <<" "<< y[i]+dy[i] <<"\n";
}

return 0;
}
