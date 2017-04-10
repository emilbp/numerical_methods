#include <functional>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <cmath>
using namespace std;

function<double(double,int)> lspline(vector<double>&x, vector<double>&y);

int main() {

int nx = 10;
int kx = 200;
double k;
vector<double> x(nx), y(nx), x_real(kx), y_real(kx), y_integ(kx), y_deriv(kx);

// Generate sampled values
for (int i = 0; i < nx; i++) {
	x[i] = (double)i;
	y[i] = cos(x[i])*cos(x[i]);
}

// Generate 'real' values
for (int i = 0; i < kx; i++) {
	k = ((double)i * (double)nx) / (double)kx;
	x_real[i] = k;
	y_real[i] = cos(x_real[i])*cos(x_real[i]);
	y_deriv[i] = -2 * sin(x_real[i]) * cos(x_real[i]);
	y_integ[i] = (x_real[i] + sin(x_real[i])*cos(x_real[i]))/2;
}

// Output sampled values
cout << "# m=0, S=4\n";
for(size_t i=0;i<x.size();i++) cout << x[i] << " " << y[i] << endl;

// Output 'real' values
cout << "# m=2, S=0\n";
for(size_t i=0;i<x_real.size();i++) cout << x_real[i] << " " << y_real[i] << endl;

cout << "# m=3, S=0\n";
for(size_t i=0;i<x_real.size();i++) cout << x_real[i] << " " << y_deriv[i] << endl;

cout << "# m=4, S=0\n";
for(size_t i=0;i<x_real.size();i++) cout << x_real[i] << " " << y_integ[i] << endl;
return 0;
}
