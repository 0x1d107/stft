#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

#include "stft.hpp"
double cdabs(std::complex<double> cd){
	return std::sqrt(cd.real()*cd.real()+cd.imag()*cd.imag());
}
int blerp(double x,double a,double b){
	double clamped = std::max(std::min(b,x),a);
	int t = (clamped-a)*255/(b-a);
	return  t;
}

int main(){
	std::vector<double> s;
	double si;
	std::cin >> si;
	while(!std::cin.eof()){
		s.push_back(si);
		std::cin >> si;
	}

	CM M = stft(s);
	double max_abs = 0.0001;
	double min_abs = 0;
	for(int i=0;i<M.rows();i++)
		for(int j=0;j< M.cols();j++){
			double a = cdabs(M(i,j));
			if(a>max_abs)
				max_abs = a;
			if(a<min_abs)
				min_abs = a;
			
		}
#ifdef PGM	
	std::cout << "P2"<<std::endl;
	std::cout<< M.cols() << ' ' << M.rows()<<std::endl;
	std::cout << 255 << std::endl;
#endif
	for(int i=0;i<M.rows();i++){
		for(int j=0;j< M.cols();j++){
			double data = cdabs(M(i,j));
			assert(data>=0);
			int c= blerp(data,min_abs,max_abs);
#ifdef PGM
			std::cout<<c<<' ';
#else
			std::cout<<data<<' ';
#endif
		}
		std::cout << std::endl;
	}
	return 0;
}
