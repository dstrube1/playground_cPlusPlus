#include "IPrintable.h"
#include <iostream>

//using namespace std;

//From lesson 191, at about 2:00

//Since it's a friend this doesn't need the scope resolution operation (i.e., Printable::...) (?)
ostream &operator<<(ostream &os, const IPrintable &obj) {
	obj.print(os);
	return os;
}