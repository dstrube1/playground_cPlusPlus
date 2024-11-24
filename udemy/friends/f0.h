#ifndef __F0_H__
#define __F0_H__

#include <string>
using namespace std;

/*
Friendship is not to be taken for granted; ie, friendship must be granted, not taken
Friendship is not symmetric (A => B does not mean B => A)
Friendship is not transitive (A => B and B => C does not mean A => C) 
*/

class f0{
	friend class f1;
	friend void sharedFromF0ToF1(f0 &f);
	friend void f2::sharedFromF0ToF2(f0 &f);
	private:
		friend int priv0;
		string name {"f0"};
		friend void getF0(f0 &f);
	public:
		f0 ();
		int getPriv0();
};

#endif //__F0_H__
