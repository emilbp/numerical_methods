#include <armadillo>

using namespace std;
using namespace arma;

tuple<vec, double> rkstep12(function<vec(double,vec)> F, double t, vec y, double h) {
	int n = y.size();
	vec yt(n), yh(n), err(n), k0(n), k12(n);

	k0 = F(t,y);
	yt = y + k0*h/2;

	k12 = F(t + h/2, yt);
	yh = y + k12*h;
	err = (k0 - k12) * h/2;

return make_tuple(yh, norm(err,2));
}

tuple<vec, double> rkstep23(function<vec(double,vec)> F, double t, vec y, double h) {
	int n = y.size();
	vec yh(n), err(n), k1(n), k2(n), k3(n), k4(n), y1(n);

	k1 = F(t,y);
	yh = y + h*k1/2;

	k2 = F(t + h/2, yh);
	yh = y + h*3*k2/4;

	k3 = F(t + 3*h/4, yh);
	yh = y + h*(2*k1/9 + k2/3 + 4*k3/9);

	k4 = F(t + h, yh);
	y1 = y + h*(7*k1/24 + k2/4 + k3/3 + k4/8);
	err = yh - y1;

return make_tuple(yh, norm(err,2));
}

tuple<vec, double> rkstep45(function<vec(double,vec)> F, double t, vec y, double h) {
	int n = y.size();
	vec yh(n), err(n), k1(n), k2(n), k3(n), k4(n), k5(n), k6(n), y1(n);

	k1 = F(t,y);
	yh = y + h*k1/4;

	k2 = F(t + h/4, yh);
	yh = y + h*(3*k1/32 + 9*k2/32);

	k3 = F(t + 3*h/8, yh);
	yh = y + h*(1932*k1/2197 - 7200*k2/2197 + 7296*k3/2197);

	k4 = F(t + 12*h/13, yh);
	yh = y + h*(439*k1/216 - 8*k2 + 3680*k3/513 - 845*k4/4104);

	k5 = F(t + h, yh);
	yh = y + h*(-8*k1/27 + 2*k2 -3544*k3/2565  + 1859*k4/4104 - 11*k5/40);

	k6 = F(t + h/2, yh);

	yh = y + h*(16*k1/135 + 6656*k3/12825 + 28561*k4/56430 - 9*k5/50 +2*k6/55);
	y1 = y + h*(25*k1/216 + 1408*k3/2565  + 2197 *k4/4104  -   k5/5);
	err = yh-y1;

return make_tuple(yh, norm(err,2));
}


void rkdriver(
	function<vec(double,vec)> & F,
	vector<double> & xlist, vector<vec> & ylist,
	string mode,
	const double b, double h, const double acc, const double eps) {

	int n = ylist.front().size();
	double a = xlist.front();
	vec y1(n); double err;

	while(xlist.back() < b) {
		double x0 = xlist.back();
		vec y0 = ylist.back();
		if (x0+h > b) { h = b-x0; }
		if (mode == "ode12") {
			tie(y1, err) = rkstep12(F, x0, y0, h);
		} else if (mode == "ode23") {
			tie(y1, err) = rkstep23(F, x0, y0, h);
		} else if (mode == "ode45") {
			tie(y1, err) = rkstep45(F, x0, y0, h);
		} else {throw invalid_argument("Stepper mode not recognized");}

		double tol = (acc + norm(y1,2)*eps)*sqrt(h/(b-a));

		if (tol > err) {
			xlist.push_back(x0+h);
			ylist.push_back(y1);
		}
		if (err > 0) {
			h = h*pow(tol/err,0.25)*0.95; // Reduce the step size
		} else {h = 2*h;} // If the error is very low, increase the step size
	}
}
