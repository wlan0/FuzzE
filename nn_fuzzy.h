/*
 *  nn_fuzzy.h
 *  open nn
 *
 *  Created by Sidhartha Mani on 08/09/11.
 *  Copyright 2011 Amrita School Of Engineering. All rights reserved.
 *
 *  Basic Type definitions, which will be the basic unit of all fuzzy sets -> nn_fuzzy
 */
#ifndef NN_FUZZY_H
#define NN_FUZZY_H
#include "nn_exception.h"
#include <map>
#include <vector>

class nn_fuzzy {
protected:
	map<double,double> set;
	map<double,double>::iterator it;
public:
	nn_fuzzy();
	void add_new(double member, double membership_value);
	void print_set();
	double get_membership_value(double member);
	vector<double> get_members();
	void erase(double member);
	void clear_all();
	bool is_normal_set();
	bool end_of_set();
	bool set_membership(double membership);
	bool set_membership(double member,double membership);
	double get_membership();
	void next_member();
	void reset_position();
	double get_member();
	size_t nn_size();
};

class nn_illegalMembershipValueException : public nn_exception {
public:
	nn_illegalMembershipValueException();
};

class nn_noMoreElementsException : public nn_exception {
public:
	nn_noMoreElementsException();
};

#endif