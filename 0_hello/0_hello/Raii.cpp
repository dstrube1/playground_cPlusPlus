//
//  Raii.cpp
//  0_hello
//
//  Created by David Strube on 2023/02/25.
//  Copyright © 2023 David Strube. All rights reserved.
//
//RAII : resource acquisition is initialization
//https://en.cppreference.com/w/cpp/language/raii
//https://en.wikipedia.org/wiki/Resource_acquisition_is_initialization

#include "Raii.hpp"
//from https://www.youtube.com/watch?v=pTMvh6VzDls
// at 8:42
//Constructor
Raii::Raii(int x){this->n = new int[x];}
//Destructor
Raii::~Raii(){delete this->n;}

int* Raii::get_n(){return this->n;}
