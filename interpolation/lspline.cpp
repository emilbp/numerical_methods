#include <functional>
#include <vector>
#include <stdexcept>
using namespace std;

function<double(double)> lspline(vector<double>&x, vector<double>&y) {
//if(y.size() != x.size()) throw logic_error("x.size != y.size");

return [x,y](double z) {
	int i = 0, j = x.size() - 1;

	while(j - i > 1) {
		int m = (i + j) / 2;
		if(z > x[m]) {
			i = m;
		}
		else {
			j = m;
		}
	};
	double p = (y[i+1] - y[i]) / (x[i+1] - x[i]);
	return y[i] + p*(z - x[i]);
};
}
