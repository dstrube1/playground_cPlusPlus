#include "PrintMe.h"
#include <iostream>

using namespace std;

PrintMe::PrintMe(){
	cout << "PrintMe constructor\n";
}

void PrintMe::print(ostream &os) const {
	os << "print from PrintMe" << endl;
}

PrintMe::~PrintMe(){
	cout << "PrintMe destructor\n";
}
