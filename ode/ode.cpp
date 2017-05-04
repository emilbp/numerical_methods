#include <armadillo>

using namespace std;
using namespace arma;

tuple<vec, double> rkstep12(function<vec(vec,vec)> F, vec t, vec y, double h) {
	int n = y.size();

	vec yt(n), yh(n), err(n);
	vec k0 = F(t,y);
	for (int i = 0; i < n; i++) {
		yt[i] = y[i] + k0[i] * h/2;
	}

	vec k12 = F(t + h/2, yt);
	for (int i = 0; i < n; i++) {
		yh[i] = y[i] + k12[i] * h/2;
	}

	for (int i = 0; i < n; i++) {
		err[i] = (k0[i] - k12[i]) * h/2;
	}

return make_tuple(yh, norm(err));
}


tuple<vec, vec> rkdriver(function<vec(vec,vec)> F, vec ystart, vec time, double h, double eps, double acc) {
	int n = ystart.size();
	uvec indices(2);
	for (int i = 0; i < n-1; i++) indices(i) = i;
	vec ys = ystart, ts = time.elem(indices);
	bool end = false;
	while (end == false) {
		double t = ts(ts.size()-1);
		double y = ys(ys.size()-1);

		if (t >= time(time.size()-1)) end = true;

		if (t+h > time(time.size()-1)) h = time(time.size()-1) - t;

		vec yh; double err;
		tie(yh, err) = rkstep12(F, t, y, h);

		double tol = (acc + norm(yh)*eps) * sqrt(h / (time(time.size()-1) - time(0)));

		if (err < tol) {
			ts.resize(ts.size()+1);
			ts(ts.size()) = t+h;
			ys.resize(ys.size()+1);
			ys(ys.size()) = yh;
		}
		if (err == 0) {
			h *= 2;
		} else {
			h *= pow(tol/err, 0.25) * 0.95;
		}
	}
return make_tuple(ts, ys);
}
