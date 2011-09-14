/*
 *  basic_defs.h
 *  open nn
 *
 *  Created by Sidhartha Mani on 07/09/11.
 *  Copyright 2011 Amrita School Of Engineering. All rights reserved.
 *
 *	Depreceated basic definitons of all fuzzy sets -- problem -- not appropriate for refactoring code 
 *
 */
#ifndef NN_BASIC_DEF_H
#define NN_BASIC_DEF_H
#include "exception.h"
#include <vector>

#define NN_COMPLEMENT_NORMAL			1
#define NN_COMPLEMENT_SUGENOCLASS		2
#define NN_TNORM_MINIMUM				1
#define NN_TNORM_PRODUCT				2
#define NN_TNORM_EINSTEIN_PRODUCT		3
#define NN_TNORM_DRASTIC_PRODUCT		4
#define NN_SNORM_MAXIMUM				1
#define NN_SNORM_SUM					2
#define NN_SNORM_EINSTEIN_SUM			3
#define NN_SNORM_DRASTIC_SUM			4


class fuzzy {		//Basic unit of fuzzy sets 
public:
	double value;  //this is the value or the real world values
	double fuzz;   //this is the membership value
};

class fuzzy_set {	//definition of a single set and its operations
private:
	vector<fuzzy> set;
public:
	fuzzy_set();
	void add_new(double member, double membership_value);	//adds another entry into the fuzzy set
//	fuzzy_set(vector<fuzzy> v);			//coverts a vector to an object of fuzzy set
	void print_set();					//prints all the members and their membership values
	void complement(int type,int parameter);					//complements the fuzzy set
	fuzzy_set t_norm(fuzzy_set op2,int type);		//Does fuzzy intersection of two sets if no parameter is specified, otherwise, does tnorm operator as per the specified parameter type
	fuzzy_set s_norm(fuzzy_set op2,int type);		//Does fuzzy union of two sets if no paramter si specified, otherwise, does snorm operator as per the specified parameter type
	//The following functions are called concepts associated with fuzzy sets
	fuzzy_set support();
	fuzzy_set core();
	bool normal_set();
	fuzzy_set crossover();
	fuzzy_set alpha_cut(double alpha);
	fuzzy_set strong_alpha_cut(double alpha);
};

#endif
