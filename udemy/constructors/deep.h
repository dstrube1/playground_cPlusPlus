#ifndef __DEEP_H__
#define __DEEP_H__

#include <string>
using namespace std;

class deep{
	private:
		int *priv0;
		string priv1 {"initial value"};
	public:
		deep (int p0, string p1);
		deep ();
		int getPriv0();

		//Copy constructor
		deep (const deep &source);

		//Destructor
		~deep();
};

#endif //__DEEP_H__
