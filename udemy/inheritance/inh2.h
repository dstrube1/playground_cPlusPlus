#ifndef __INH2_H__
#define __INH2_H__

#include <string>
#include "inh1.h"

using namespace std;

//final keyword here makes sure that this class cannot be derived from
class inh2 final: public inh1 {
	public:
		inh2(); 
		virtual void virtualMethod() const override;
		virtual ~inh2();
};

#endif //__INH2_H__
/*
//interface example:
class Printable{
	friend ostream &operator<<(ostream &, const Printable &obj);
	public:
		virtual void print(ostream &os) const = 0;
		virtual Printable(){/ *not sure if this is permissible:* / cout "Printable destructor\n";};
};

*/
