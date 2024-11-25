#include "f0.h"
#include <iostream>

using namespace std;

/*
	private:
		int priv0;
		string priv1 {"initial value"};
*/

f0::f0 (){
	priv0 = 1;
	cout << "F0 contructor with no params" << endl;
}

int f0::getPriv0() {
	cout << __func__ << " called by " << priv1 << endl;
	return priv0;
}
