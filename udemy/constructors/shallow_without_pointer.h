#ifndef __SHALLOW_WOP_H__
#define __SHALLOW_WOP_H__

#include <string>

using namespace std;

class shallow_without_pointer{
	private:
		int priv0; 								//<-not a pointer
		string priv1 {"shallow_without_pointer initial value"};
	public:
		//Standard constructor declarations
		shallow_without_pointer (int p0, string p1);
		shallow_without_pointer ();

		int getPriv0();
		void setPriv1(string p1);

		//Copy constructor
		shallow_without_pointer (const shallow_without_pointer &source);

		//Destructor
		~shallow_without_pointer();
};

#endif //__SHALLOW_WOP_H__

