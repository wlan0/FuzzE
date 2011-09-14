/*
 *  exception.h
 *  open nn
 *
 *  Created by Sidhartha Mani on 07/09/11.
 *  Copyright 2011 Amrita School Of Engineering. All rights reserved.
 *
 */

#ifndef NNEXCEPTION_H
#define NNEXCEPTION_H
#include<iostream>
using namespace std;
#include <strings.h>

class open_nn_exception {
protected:
	string stmt;
public:
	void statement();
};	

class illegalMembershipValueException : public open_nn_exception {
	public:
	illegalMembershipValueException();
};

class incompatibleFuzzySetsException : public open_nn_exception {
public:
	incompatibleFuzzySetsException();
};	

#endif