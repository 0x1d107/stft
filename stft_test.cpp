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
	double max_abs = 0;
	for(int i=0;i<M.rows();i++)
		for(int j=0;j< M.cols();j++)
			if(cdabs(M(i,j))>max_abs)
				max_abs = cdabs(M(i,j));
	
	std::cout << "P2"<<std::endl;
	std::cout<< M.cols() << ' ' << M.rows()<<std::endl;
	std::cout << 255 << std::endl;
	for(int i=0;i<M.rows();i++){
		for(int j=0;j< M.cols();j++){
			int c= blerp(cdabs(M(i,j)),0,max_abs);
			std::cout<<c<<' ';
		}
		std::cout << std::endl;
	}
	return 0;
}
