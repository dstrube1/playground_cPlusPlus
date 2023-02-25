//
//  Raii.hpp
//  0_hello
//
//  Created by David Strube on 2023/02/25.
//  Copyright © 2023 David Strube. All rights reserved.
//

#ifndef Raii_hpp
#define Raii_hpp

#include <stdio.h>

//from https://www.youtube.com/watch?v=pTMvh6VzDls
// at 8:42
class Raii{
private:
    int *n;
public:
    //Constructor
    Raii(int x);

    //Destructor
    ~Raii();

    int* get_n();

};


#endif /* Raii_hpp */
