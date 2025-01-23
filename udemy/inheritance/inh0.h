#ifndef __INH0_H__
#define __INH0_H__

#include <string>
using namespace std;

/*
*/

class inh0{
	private:
		string name; 
		//~inh0(); //destructor can be private; but if it's private in base, then must be private in derived
	protected:
		string protectedString;
	public:
		inh0();
		inh0(string);
		virtual void display() const;
		string getName();
		string getProtectedString();
		virtual void virtualMethod() const;
		virtual ~inh0(); 
};

#endif //__INH0_H__
/*
TODO: 

using base class references:
inh1 i1_origin;
inh0 &i1_ref = i1_origin;
i1_ref.virtualMethod();

abstract class: if a class has at least 1 pure virtual function, or inherits from another abstract class and itself has no non-virtual functions*
new abstract base class inh, from which inh0 inherits ?
virtual void virtualMethod() = 0; // pure virtual function
virtual ~inh() {cout << "inh destructor\n";}
inh i; //can't instantiate inh like this
inh *i_ptr = new ihn(); //or this
//but can do this:
//inh *i_ptr = new inh0();
*: test this: what if inh4 derives from inh, and has no non-automatic (constructor / desctructor) method? can I create it like this?
inh4 i4;
//to pass a vector of pointers as a reference (so as to not copy anything):
void doStuff(vector<inh *> &vec){
	for(const auto i : vec){
		i.virtualMethod();
	}
}

*/