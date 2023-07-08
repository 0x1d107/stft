#include "stft.hpp"
#include "unsupported/Eigen/FFT"
#include <complex>
#include <iostream>
double hann_window(int n,int N){
	if(n<0||n>N)
		return 0;
	double s = sin(M_PI*n/(N-1));
	return s*s;
}
double fullspec_window(int n,int N){
	return 1;
}
wfunc_t window = hann_window;
int fs = 128;
int overlap = fs/2;
CM stft(std::vector<double> &signal){
	
	//
	Eigen:Eigen::FFT<double>fft;
	int window_step = fs - overlap;
	int T = signal.size()/window_step;
	CM stftm(T,fs);
	for(int i=0;i<T;i++){
		std::vector<double> f(fs);
		for(int j=0;j<fs;j++){
			f[j] = window(j,fs) * signal[j+i*window_step];
		}
		std::vector<std::complex<double>> frq(fs,0);
		fft.fwd(frq,f);
		for(int j=0;j<fs;j++){
			stftm(i,j) = frq[j];
		}


	}
	stftm.transposeInPlace();
	return stftm;
}
std::vector<double>  istft(CM& spectrum){
	spectrum.transposeInPlace();
	Eigen::FFT<double> fft;
	int window_step = fs - overlap;
	int T = spectrum.rows();
	int length = (T-1)*window_step+fs;
	std::vector<double> signal(length);
	for(int i=0;i<T;i++){
		std::vector<std::complex<double>> frq(fs,0);
		std::vector<double> f(fs);
		for(int j = 0; j < fs;j++)
			frq[j] = spectrum(i,j);
		fft.inv(f,frq);
		for(int j = 0; j < fs;j++)
			if(window(j,fs)>0)signal[j+window_step*i] = f[j]/window(j,fs);
		

	}

	return signal;	
}
