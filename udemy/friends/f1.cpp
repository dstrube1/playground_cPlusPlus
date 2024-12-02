#include "f1.h"
#include <iostream>

using namespace std;

f1::f1() { 
	name = "f1";
	cout << "created an f1" << endl; 
}

void f1::sharedFromF0(f0 &f0_obj) {
	cout << __func__ << ": simple: ";
	cout << f0_obj.getPriv0() << "; ";
	cout << f0_obj.getName() << endl;
	
	cout << "complicated: ";
	cout << "priv0: " << f0_obj.priv0 << "; ";
	cout << "++priv0: " << ++f0_obj.priv0 << "; ";
	cout << "name change: "; 
	f0_obj.name = "f0 changed by f1";
	cout << f0_obj.name << endl;
	
	cout << "hardcore: ";
	cout << "static_num: " << f0::static_num << "; ";
	cout << "++static_num: " << ++f0::static_num << endl;
}

void f1::doF0Stuff(){
	cout << __func__ << ": simple: ";
	f0 f0_obj;
	cout << f0_obj.getPriv0() << "; ";
	cout << f0_obj.getName() << endl;
	
	cout << "complicated: ";
	cout << "priv0: " << f0_obj.priv0 << "; ";
	cout << "++priv0: " << ++f0_obj.priv0 << "; ";
	cout << "name change: "; 
	f0_obj.name = "f0 changed by f1 from "; // << f0_obj.name + __func__ ;
// error: invalid operands to binary expression ('const char[23]' and 'const char[10]')
	cout << f0_obj.name << __func__ << endl;
	
	cout << "hardcore: ";
	cout << "static_num: " << f0::static_num << "; ";
	cout << "++static_num: " << ++f0::static_num << endl;
}