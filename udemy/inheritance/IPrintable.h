#ifndef __IPRINTABLE_H__
#define __IPRINTABLE_H__

#include <iostream>

using namespace std;


//interface example:
//Good practice to have interfaces start with I
class IPrintable{
	//abstract class: if a class has at least 1 pure virtual function, or inherits from another abstract class and itself has no non-virtual functions*

	friend ostream &operator<<(ostream &, const IPrintable &obj);
	public:
		virtual void print(ostream &os) const = 0; //the "= 0" is what makes this a pure virtual function
		//An abstract class cannot be instantiated 
		
		//constructor cannot be virtual 
		IPrintable(){cout << "IPrintable constructor\n";}
		
		//If a class has a pure virtual function AND a constructor,
		//it will compile but won't be useful because it can't be instantiated
		
		virtual ~IPrintable(){cout << "IPrintable destructor\n";}
};


#endif //__IPRINTABLE_H__