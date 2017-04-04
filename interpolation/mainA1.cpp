#include <functional>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <cmath>
using namespace std;

function<double(double)> lspline(vector<double>&x, vector<double>&y);

int main() {

int nx = 10;
vector<double> x(nx), y(nx);

// Generate sampled values
for (int i = 0; i < nx; i++) {
	//x[i] = i + 0.5 * sin(i);
	//y[i] = i + cos(i * i);
	x[i] = i / M_PI;
	y[i] = cos(x[i] * i);
}

// Output sampled values
for(size_t i=0;i<x.size();i++) cout << x[i] << " " << y[i] << endl;

auto ls = lspline(x, y);

int N = 20; double step = (x.back() - x.front()) / (N - 1);

for(double z = x.front(); z < x.back(); z += step) {
	cout << z << " " << ls(z) << endl;
}

return 0;
}

