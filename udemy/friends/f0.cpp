#include "f0.h"
#include <iostream>

using namespace std;

/*static*/ int f0::static_num = 1; 

f0::f0 (){
	name = "f0";
	priv0 = static_num + 1;
	cout << "F0 contructor with no params; priv0 = " << priv0 << endl;
}

int f0::getPriv0(){ 
	cout << __func__ << ": ";
	return priv0; 
}

string f0::getName() { 
	cout << __func__ << ": ";
	return name; 
}