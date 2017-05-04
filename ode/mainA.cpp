#include <iostream>
#include <armadillo>

using namespace arma;
using namespace std;

tuple<vec, double> rkstep12(function<vec(vec, vec)> F, vec t, vec y, double h);
tuple<vec, vec> rkdriver(function<vec(vec,vec)> F, vec ystart, vec time, double h, double eps, double acc);

int main() {

	function<vec(vec, vec)> f1 = [] (vec x, vec y) {
		int n = x.size(); vec z(n);
		z[0] = -y[1]; z[1] = y[0];
		return z;
	};


	vec time = {0, 3}, ystart = {0, 10};

	time.print("x"); ystart.print("y");
	f1(time,ystart).print("f(x,y)");

	vec t; double y;
//	tie(t, y) = rkdriver(f1, ystart, time, 0.01, 0.01, 0.01);

	t.print("t is");
	cout << "y is " << y << endl;
return 0;
}
