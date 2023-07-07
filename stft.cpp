#include "stft.hpp"
#include "unsupported/Eigen/FFT"
#include <complex>
double hann(int n,int N){
	int s = sin(M_PI*n/N);
	return s*s;
}
wfunc_t window = hann;
int fs = 64;
CM stft(std::vector<double> &signal){
	Eigen:Eigen::FFT<double>fft;
	
	//
	CM stftm(signal.size(),fs);
	for(int i=0;i<signal.size();i++){
		std::vector<double> f(fs);
		for(int j=0;j<fs;j++){
			f[j] = window(j-i,fs) * signal[j];
		}
		std::vector<std::complex<double>> frq;
		fft.fwd(frq,f);
		for(int j=0;j<fs;j++){
			stftm(i,j) = frq[j];
		}

	}

	return stftm;
}
