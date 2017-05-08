#include <armadillo>

using namespace std;
using namespace arma;

tuple<vec, double> rkstep12(function<vec(double,vec)> F, double t, vec y, double h) {
	int n = y.size();

	vec yt = zeros(n), yh = zeros(n), err = zeros(n);
	vec k0 = F(t,y);
	for (int i = 0; i < n; i++) {
		yt[i] = y[i] + k0[i] * h/2;
	}

	vec k12 = F(t + h/2, yt);
	for (int i = 0; i < n; i++) {
		yh[i] = y[i] + k12[i] * h;
	}

	for (int i = 0; i < n; i++) {
		err[i] = (k0[i] - k12[i]) * h/2;
	}

return make_tuple(yh, norm(err));
}

tuple<vec, double> rkstep32(function<vec(double,vec)> F, double t, vec y, double h) {
	int n = y.size();
	vec yt = zeros(n), ye = zeros(n), err = zeros(n);
	vec k1(n), k2(n), k3(n), k4(n);
	k1 = F(t,y);
	for (int i = 0; i < n; i++) {
		yt[i] = y[i] + (1/2) * k1[i] * h;
	}
	k2 = F(t + h/2, yt);
	for (int i = 0; i < n; i++) {
		yt[i] = y[i] + (3/4) * k2[i] * h;
	}

	k3 = F(t + 3/4 * h, yt);
	for (int i = 0; i < n; i++) {
		ye[i] = y[i] + ((2/9) * k1[i] + (1/3) * k2[i] + (4/9) * k3[i]) * h;
	}

	k4 = F(t + h, yt);
	for (int i = 0; i < n; i++) {
		yt[i] = y[i] + ((7/24) * k1[i] + (1/4) * k2[i] + (1/3) * k3[i] + (1/8) * k4[i]) * h;
		err[i] = ye[i] - yt[i];
	}

return make_tuple(ye, norm(err));
}

tuple<vec, double> rkstep45(function<vec(double,vec)> F, double t, vec y, double h) {
	int n = y.size();
	vec yt = zeros(n), ye = zeros(n), err = zeros(n);
	vec k1 = F(t,y);
	for (int i = 0; i < n; i++) {
		yt[i] = y[i] + 1/4 * k1[i] * h;
	}

	vec k2 = F(t + h/4, yt);
	for (int i = 0; i < n; i++) {
		yt[i] = y[i] + (3/32 * k1[i] + 9/32 * k2[i]) * h;
	}

	vec k3 = F(t + 3/8 * h, yt);
	for (int i = 0; i < n; i++) {
		yt[i] = y[i] + (1932/2197 * k1[i] -7200*2197 * k2[i] + 7296/2197 * k3[i]) * h;
	}

	vec k4 = F(t + 12/13 * h, yt);
	for (int i = 0; i < n; i++) {
		yt[i] = y[i] + (439/213 * k1[i] -8 * k2[i] + 3680/513 * k3[i] - 845/4104 * k4[i]) * h;
	}

	vec k5 = F(t + h, yt);
	for (int i = 0; i < n; i++) {
		yt[i] = y[i] + (-8/27 * k1[i] + 2 * k2[i] - 3544/2565 * k3[i] + 1859/4104 * k4[i] - 11/40 * k5[i]) * h;
	}

	vec k6 = F(t + h/2, yt);

	for (int i = 0; i < n; i++) {
		ye[i] = y[i] + (16/135 * k1[i] + 6656/12825 * k3[i] + 28561/56430 * k4[i] - 9/50 * k5[i] + 2/55 * k6[i]) * h;
		yt[i] = y[i] + (25/216 * k1[i] - 1408/2565 * k3[i] + 2197/4104 * k4[i] - 1/5 * k5[i]) * h;
		err[i] = ye[i] - yt[i];
	}
return make_tuple(ye, norm(err));
}


void rkdriver(
	function<vec(double,vec)> & F,
	vector<double> & xlist, vector<vec> & ylist,
	string mode,
	double b, double h, double acc, double eps) {

	int n = ylist.front().size();
	double a = xlist.front();
	vec y1(n); double err;

	while(xlist.back() < b) {
		double x = xlist.back();
		vec y = ylist.back();
		if (x+h > b) h = b-x;
		if (mode == "ode12") {tie(y1, err) = rkstep12(F, x, y, h);}
		else if (mode == "ode32") {tie(y1, err) = rkstep32(F, x, y, h);}
		else if (mode == "ode45") {tie(y1, err) = rkstep45(F, x, y, h);}
		else {throw invalid_argument("Stepper mode not recognized");}

		double tol = (acc + norm(y1,2)*eps)*sqrt(h/(b-a));

		if (tol > err) {
			xlist.push_back(x+h);
			ylist.push_back(y1);
		}
		if (err > 0) {
			h = h*pow(tol/err,0.25)*0.95;
		} else {h = 2*h;}
	}
}
