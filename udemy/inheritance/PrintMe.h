#ifndef __PRINTME_H__
#define __PRINTME_H__

#include <iostream>
#include "IPrintable.h"

using namespace std;


class PrintMe : public IPrintable{
	public:
		PrintMe();
		void print(ostream &os) const override;
		virtual ~PrintMe();
};

#endif //__PRINTME_H__