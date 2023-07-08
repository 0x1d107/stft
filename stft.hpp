#pragma once
#include "Eigen/Core"
#include "unsupported/Eigen/FFT"
#include <complex>

typedef double (*wfunc_t)(int n,int N);
typedef Eigen::Matrix<std::complex<double>,Eigen::Dynamic,Eigen::Dynamic> CM;

extern wfunc_t window;

CM stft(std::vector<double> &signal,int nperseg = 64,int overlap = 32);
std::vector<double>  istft(CM& spectrum,int nperseg = 64,int overlap = 32);
void getTimeFreq(double fs,int nperseg, int overlap,int len, std::vector<double> &time, std::vector<double> &frq);

