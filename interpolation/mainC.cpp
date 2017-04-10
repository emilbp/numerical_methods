#include <functional>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <cmath>
using namespace std;

function<double(double, int)> cspline(vector<double>&x, vector<double>&y);

int main() {

int nx = 10;
int kx = 200;
double k;
vector<double> x(nx), y(nx), x_real(kx), y_real(kx);

// Generate sampled values
for (int i = 0; i < nx; i++) {
	x[i] = (double)i/2;
	//y[i] = pow(x[i],2) - 1;
	y[i] = cos(x[i]*5);
}

// Generate 'real' values
for (int i = 0; i < kx; i++) {
	k = ((double)i * (double)nx) / (double)kx;
	x_real[i] = k/2;
	//y_real[i] = pow(x_real[i],2) - 1;
	y_real[i] = cos(x_real[i]*5);
}

// Output sampled values
cout << "# m=0, S=4\n";
for(size_t i=0;i<x.size();i++) cout << x[i] << " " << y[i] << endl;


// Output 'real' values
cout << "# m=2, S=0\n";
for(size_t i=0;i<x_real.size();i++) cout << x_real[i] << " " << y_real[i] << endl;


// Make the linear spline
auto cs = cspline(x, y);

int N = 200; double step = (x.back() - x.front()) / (N - 1);

cout << "# m=1, S=0\n";
for(double z = x.front(); z < x.back(); z += step) {
	cout << z << " " << cs(z,0) << endl;
}
cout << "# m=3, S=0\n";
for(double z = x.front(); z < x.back(); z += step) {
	cout << z << " " << cs(z,-1) << endl;
}
cout << "# m=4, S=0\n";
for(double z = x.front(); z < x.back(); z += step) {
	cout << z << " " << cs(z,1) << endl;
}
return 0;
}
