#include "PrintMe.h"
#include <iostream>

using namespace std;

PrintMe::PrintMe(){
	cout << "PrintMe constructor\n";
}

void PrintMe::print(ostream &os) const {
	//to set precision to 2 decimal places:
	//os.precision(2);
	//to set fixed point:
	//os << std::fixed;
	os << "print from PrintMe" << endl;
}

PrintMe::~PrintMe(){
	cout << "PrintMe destructor\n";
}
