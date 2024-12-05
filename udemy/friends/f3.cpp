#include "f3.h"
#include <iostream>

using namespace std;

f3::f3() { 
	name = "f3";
	cout << "created an f3" << endl; 
}

void f3::sharedFromF0(f0 &f0_obj) {
	cout << __func__ << ": simple: ";
	cout << f0_obj.getPriv0() << "; "; 
	cout << f0_obj.getName() << endl;
	
	//NOT ALLOWED
	/**
	cout << "complicated: ";
	cout << "priv0: " << f0_obj.priv0 << "; ";
	//error: 'priv0' is a private member of 'f0'
	cout << "++priv0: " << ++f0_obj.priv0 << "; ";
	cout << "name change: "; 
	f0_obj.name = "f0 changed by f3";
	cout << f0_obj.name << endl;
	
	cout << "hardcore: ";
	cout << "static_num: " << f0::static_num << "; ";
	cout << "++static_num: " << ++f0::static_num << endl;
	**/
}

void f3::doF0Stuff(){
	cout << __func__ << ": simple: ";
	f0 f0_obj;
	cout << f0_obj.getPriv0() << "; ";
	cout << f0_obj.getName() << endl;
	
	//NOT ALLOWED
	/**
	cout << "complicated: ";
	cout << "priv0: " << f0_obj.priv0 << "; ";
	cout << "++priv0: " << ++f0_obj.priv0 << "; ";
	cout << "name change: "; 
	f0_obj.name = "f0 changed by f2 from "; 
	cout << f0_obj.name << __func__ << endl;
	
	cout << "hardcore: ";
	cout << "static_num: " << f0::static_num << "; ";
	cout << "++static_num: " << ++f0::static_num << endl;
	**/
}