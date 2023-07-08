#include "stft.hpp"
#include <iostream>
int main(){

	std::vector<double> s;
	double si;
	std::cin >> si;
	while(!std::cin.eof()){
		s.push_back(si);
		std::cin >> si;
	}

	CM M = stft(s);
	std::vector<double> rr = istft(M);
	for(double i: rr){
		std::cout << i <<std::endl;
	}
	

	return 0;
}
