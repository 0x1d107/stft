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
CM stft(std::vector<double> &signal,int nperseg,int overlap){
	
	//
	Eigen:Eigen::FFT<double>fft;
	int window_step = nperseg - overlap;
	int T = signal.size()/window_step;
	CM stftm(T,nperseg);
	for(int i=0;i<T;i++){
		std::vector<double> f(nperseg);
		for(int j=0;j<nperseg;j++){
			f[j] = window(j,nperseg) * signal[j+i*window_step];
		}
		std::vector<std::complex<double>> frq(nperseg,0);
		fft.fwd(frq,f);
		for(int j=0;j<nperseg;j++){
			stftm(i,j) = frq[j];
		}


	}
	stftm.transposeInPlace();
	return stftm;
}
std::vector<double>  istft(CM& spectrum,int nperseg,int overlap){
	spectrum.transposeInPlace();
	Eigen::FFT<double> fft;
	int window_step = nperseg - overlap;
	int T = spectrum.rows();
	int length = (T-1)*window_step+nperseg;
	std::vector<double> signal(length);
	for(int i=0;i<T;i++){
		std::vector<std::complex<double>> frq(nperseg,0);
		std::vector<double> f(nperseg);
		for(int j = 0; j < nperseg;j++)
			frq[j] = spectrum(i,j);
		fft.inv(f,frq);
		for(int j = 0; j < nperseg;j++)
			if(window(j,nperseg)>0)signal[j+window_step*i] = f[j]/window(j,nperseg);
		

	}

	return signal;	
}
void getTimeFreq(double fs,int nperseg, int overlap,int len, std::vector<double> &time, std::vector<double> &frq){
	frq.resize(len);
	for(int i=0;i< len;i++)
		frq[i] = i*fs/len;
	double total_time = len/fs;
	int window_step = nperseg - overlap;
	int T = len/window_step;
	time.resize(T);

	for(int i=0;i<T;i++){
		time[i] = i*total_time/T;
	}

}
