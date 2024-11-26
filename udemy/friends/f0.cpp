#include "f0.h"
#include <iostream>

using namespace std;

/*
	private:
		int priv0;
		string name {"initial value"};
*/

/*static*/ int f0::static_num {1}; //TODO: can this be modified by the friend class f1?

f0::f0 (){
	priv0 = static_num + 1;
	cout << "F0 contructor with no params" << endl;
}
