/*
 *  exception.cpp
 *  open nn
 *
 *  Created by Sidhartha Mani on 07/09/11.
 *  Copyright 2011 Amrita School Of Engineering. All rights reserved.
 *
 */

#include "exception.h"

void open_nn_exception::statement() {
	cout<<stmt;
}

illegalMembershipValueException::illegalMembershipValueException() {
	stmt = new char[100];
    stmt = "The membership value does not lie between 0 and 1, inclusive";
}

incompatibleFuzzySetsException::incompatibleFuzzySetsException() {
	stmt = new char[100];
	stmt = "The Two or more Fuzzy sets are not compatible for the operator chosen";
}



