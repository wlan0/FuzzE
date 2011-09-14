/*
 *  nn_exception.h
 *  open nn
 *
 *  Created by Sidhartha Mani on 09/09/11.
 *  Copyright 2011 Amrita School Of Engineering. All rights reserved.
 *
 */

#ifndef NN_EXCEPTION_H
#define NN_EXCEPTION_H
#include<iostream>
using namespace std;
#include <strings.h>

class nn_exception {
protected:
	string stmt;
public:
	void statement();
};	

#endif