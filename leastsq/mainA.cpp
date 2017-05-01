#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

void qr_gs_dec(mat&, mat&);
void qr_gs_solve(mat&, mat&, vec&);
void lsfit(vec&, vec&, vec&, const std::vector<std::function<double(double)>>&, vec&, mat&);

int main() {
arma_rng::set_seed_random();

vec x, y, dy;
x  = {0.100, 0.145, 0.211, 0.307, 0.447, 0.649, 0.944, 1.372, 1.995, 2.900};
y  = {12.644, 9.235, 7.377, 6.460, 5.555, 5.896, 5.673, 6.964, 8.896, 11.355};
dy = {0.858, 0.359, 0.505, 0.403, 0.683, 0.605, 0.856, 0.351, 1.083, 1.002};
int n = x.size();

std::vector<std::function<double(double)>> funs;
funs.push_back([](double x){return 1.0;});
funs.push_back([](double x){return x;});
funs.push_back([](double x){return 1/x;});

auto fit_fun = [&](vec c,double x){
double s=0;
for(int i=0;i<c.size();i++) s+= c[i]*funs[i](x);
return s;
};
auto fun_to_fit = [](double x){return 1.+2.*x+3./x;};

int m=funs.size();
mat S(m,m);
vec c(m);

lsfit(x,y,dy,funs,c,S);


vec dc(m);

for (int i = 0; i < m; i++) dc[i] = sqrt(S(i,i));

int nx = 100;
vec h = linspace(0.09, 3, nx);

//cout << "\"data points\"" << endl;
for (int i = 0; i < n; i++) {
	cout << x[i] <<" "<< y[i] << " " << dy[i] << endl;
}
cout << endl << endl;

//cout << "\"fit\"" << endl;
for (int i = 0; i < nx; i++) {
	cout << h[i] << " " << fit_fun(c,h[i]) << " " << fit_fun(c+dc, h[i]) << " " << fit_fun(c-dc, h[i]) << endl;
}

return 0;
}
