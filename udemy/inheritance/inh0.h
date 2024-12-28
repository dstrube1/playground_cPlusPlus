#ifndef __INH0_H__
#define __INH0_H__

#include <string>
using namespace std;

/*
*/

class inh0{
	private:
		string name; 
		~inh0(); //can the destructor be private?
	protected:
		string protectedString;
	public:
		inh0();
		inh0(string);
		string getName();
		string getProtectedString();
};

#endif //__INH0_H__
