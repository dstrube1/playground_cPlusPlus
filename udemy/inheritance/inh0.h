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
