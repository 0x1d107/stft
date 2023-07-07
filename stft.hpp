#pragma once
#include "Eigen/Core"
#include "unsupported/Eigen/FFT"
#include <complex>

typedef double (*wfunc_t)(int n,int N);
typedef Eigen::Matrix<std::complex<double>,Eigen::Dynamic,Eigen::Dynamic> CM;


CM stft(std::vector<double> &signal);
