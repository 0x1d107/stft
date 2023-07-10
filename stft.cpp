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
/* Applies STFT-transform to signal.
 * global wfunc_t window - window to use in the transform. default: hann_window
 * std::vector<double> &signal - signal to transform
 * int nperseg - width of the window
 * int overlap - width of the overlap between windows
 * returns complex matrix of the spectrum
 */
CM stft(std::vector<double> &signal,int nperseg,int overlap){
	
	//
	Eigen:Eigen::FFT<double>fft;
	int window_step = nperseg - overlap;
	int T = (signal.size()/window_step)+((signal.size()%window_step)>0)+1;
	CM stftm(nperseg,T);
	for(int i=0;i<T;i++){
		std::vector<double> f(nperseg);
		for(int j=0;j<nperseg;j++){
			f[j] = window(j,nperseg) * signal[j+i*window_step];
		}
		std::vector<std::complex<double>> frq(nperseg,0);
		fft.fwd(frq,f);
		for(int j=0;j<nperseg;j++){
			stftm(j,i) = frq[j];
		}


	}
	return stftm;
}
/* Applies inverse STFT-transform to spectrum matrix to restore signal.
 * global wfunc_t window - window to use in the transform. default: hann_window
 * const CM &spectrum - spectrum to transform
 * int nperseg - width of the window
 * int overlap - width of the overlap between windows
 * returns the original signal
 */
std::vector<double>  istft(const CM& spectrum,int nperseg,int overlap){
	Eigen::FFT<double> fft;
	int window_step = nperseg - overlap;
	int T = spectrum.cols();
	int length = (T-1)*window_step+nperseg;
	std::vector<double> signal(length);
	for(int i=0;i<T;i++){
		std::vector<std::complex<double>> frq(nperseg,0);
		std::vector<double> f(nperseg);
		for(int j = 0; j < nperseg;j++)
			frq[j] = spectrum(j,i);
		fft.inv(f,frq);
		for(int j = 0; j < nperseg;j++)
			if(window(j,nperseg)>0)
				signal[j+window_step*i] = f[j]/window(j,nperseg);
		

	}

	return signal;	
}
/* Calculates time and frequency at each point of the spectrogram.
 * double fs - sampling frequency
 * int nperseg - width of the STFT-transform window
 * int overlap - amount of overlap between windows
 * int len - length of the signal vector
 * std::vector<double> &time - time steps output vector
 * std::vector<double> &frq - frequency steps output vector
 * 
 */
void getTimeFreq(double fs,int nperseg, int overlap,int len, std::vector<double> &time, std::vector<double> &frq){
	frq.resize(len);
	for(int i=0;i< len;i++)
		frq[i] = i*fs/len;
	double total_time = len/fs;
	int window_step = nperseg - overlap;
	int T = (len/window_step)+((len%window_step)>0)+1;
	time.resize(T);

	for(int i=0;i<T;i++){
		time[i] = i*total_time/T;
	}

}
