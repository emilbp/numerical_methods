#include <iostream>
#include <iomanip>
#include <complex>
#include <cmath>

std::complex<double> I0(std::complex<double> z2) {
	std::complex<double> ans;
	ans = z2+(3.0 + one_i);
	return ans;
}

int main()
{
	typedef std::complex<double> dcomp;    // your typedef
	//using namespace std::literals;
	std::cout << std::fixed << std::setprecision(1);

	dcomp one_i(0.0, 1.0);
	dcomp z = 1. - 2.*one_i;
	std::cout << "z: " << z << std::endl;
	std::cout << "I0(z): " << I0(z) << std::endl;


/*
    dcomp z1 = one_i * one_i;     // imaginary unit squared
    std::cout << "i * i = " << z1 << '\n';
	
    dcomp z2 = std::pow(one_i, 2); // imaginary unit squared
    std::cout << "pow(i, 2) = " << z2 << '\n';
	
    double PI = std::acos(-1);
    dcomp z3 = std::exp(one_i * PI); // Euler's formula
    std::cout << "exp(i, pi) = " << z3 << '\n';
	
    dcomp two_i(0.0, 2.0);					     
    dcomp z4 = 1. + two_i, z5 = 1. - two_i; // conjugates
    std::cout << "(1+2i)*(1-2i) = " << z4*z5 << '\n';
*/
}
