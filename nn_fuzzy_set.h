/*
 *  nn_fuzzy_set.h
 *  open nn
 *
 *  Created by Sidhartha Mani on 09/09/11.
 *  Copyright 2011 Amrita School Of Engineering. All rights reserved.
 *
 */
#ifndef NN_FUZZY_SET_H
#define NN_FUZZY_SET_H
#include "nn_fuzzy.h"

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

/*The Functions in class nn_fuzzy_set depend only on the functions defined in nn_fuzzy, therefore, you can refactor that completely without touching this, this makes this project data structurally easy-upgradable */

class nn_fuzzy_set : public nn_fuzzy {
public:
	bool complement(int type,int parameter);					//complements the fuzzy set
	nn_fuzzy_set t_norm(nn_fuzzy_set op2,int type);		//Does fuzzy intersection of two sets if no parameter is specified, otherwise, does tnorm operator as per the specified parameter type
	nn_fuzzy_set s_norm(nn_fuzzy_set op2,int type);		//Does fuzzy union of two sets if no paramter si specified, otherwise, does snorm operator as per the specified parameter type
	//The following functions are called concepts associated with fuzzy sets
	nn_fuzzy_set support();
	nn_fuzzy_set core();
	bool normal_set();
	nn_fuzzy_set crossover();
	nn_fuzzy_set alpha_cut(double alpha);
	nn_fuzzy_set strong_alpha_cut(double alpha);
	bool is_convex(double lambda);
};

class nn_incompatibleFuzzySetsException : public nn_exception {
public:
	nn_incompatibleFuzzySetsException();
};	

#endif
