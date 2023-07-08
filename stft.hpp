#pragma once
#include "Eigen/Core"
#include "unsupported/Eigen/FFT"
#include <complex>

typedef double (*wfunc_t)(int n,int N);
typedef Eigen::Matrix<std::complex<double>,Eigen::Dynamic,Eigen::Dynamic> CM;

extern wfunc_t window;

CM stft(std::vector<double> &signal,int fs = 64,int overlap = 32);
std::vector<double>  istft(CM& spectrum,int fs = 64,int overlap = 32);

