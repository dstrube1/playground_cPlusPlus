#include "f2.h"
#include "f0.h"
#include <iostream>

using namespace std;

f2::f2 () { 
	name = "f2";
	cout << "created an f2" << endl; 
}

void f2::sharedFromF0(f0 &f0_obj) {
	cout << __func__ << ": simple: ";
	cout << f0_obj.getPriv0() << "; ";
	cout << f0_obj.getName() << endl;
	// error: member access into incomplete type 'f0'
	//unless: #include "f0.h"
	
	cout << "complicated: ";
	cout << "priv0: " << f0_obj.priv0 << "; ";
	cout << "++priv0: " << ++f0_obj.priv0 << "; ";
	cout << "name change: "; 
	f0_obj.name = "f0 changed by f2";
	cout << f0_obj.name << endl;
	
	cout << "hardcore: ";
	cout << "static_num: " << f0::static_num << "; ";
	cout << "++static_num: " << ++f0::static_num << endl;
	/**/
}

void f2::doF0Stuff(){
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