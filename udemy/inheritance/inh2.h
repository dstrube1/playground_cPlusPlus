#ifndef __INH2_H__
#define __INH2_H__

#include <string>
#include "inh1.h"
#include <iostream>

using namespace std;

//final keyword here makes sure that this class cannot be derived from
class inh2 final: public inh1 {
	public:
		inh2(); 
		virtual void virtualMethod() const override;
		virtual ~inh2();
};


/**/
//1- Is it okay to define two classes in 1 .h file?
//2- interface example:
class Printable{
	friend ostream &operator<<(ostream &, const Printable &obj);
	public:
		virtual void print(ostream &os) const = 0; //the "= 0" is what makes this a pure virtual function
		//An abstract class cannot be instantiated and has only pure virtual functions
		
		//constructor cannot be virtual 
		//Printable(){cout << "Printable destructor\n";}
		
		//TODO: What if a class has a pure virtual function AND a constructor? Can it be instantiated?
};

/**/

#endif //__INH2_H__

