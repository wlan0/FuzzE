/*
 *  nn_fuzzy_set.cpp
 *  open nn
 *
 *  Created by Sidhartha Mani on 09/09/11.
 *  Copyright 2011 Amrita School Of Engineering. All rights reserved.
 *
 */

#include "nn_fuzzy_set.h"

bool nn_fuzzy_set::complement(int type = NN_COMPLEMENT_NORMAL, int parameter = 1) {
	switch (type)
	{
		case NN_COMPLEMENT_NORMAL:					// perform complement by the normal complement method like in crisp sets
			reset_position();
			while(!end_of_set()) {
				set_membership(1 - get_membership());
				next_member();
			}
			return true;
		case NN_COMPLEMENT_SUGENOCLASS:			// perform complement by the sugeno class of operators
			reset_position();
			while(!end_of_set()) {
				set_membership((1 - get_membership()) / (1 + (parameter * get_membership())));
				next_member();
			}
			return true;
		default:
			return NULL;
	}
}

nn_fuzzy_set nn_fuzzy_set::t_norm(nn_fuzzy_set op2,int type = NN_TNORM_MINIMUM) {
	nn_fuzzy_set result;
	reset_position();
	op2.reset_position();
	if (nn_size() != op2.nn_size()) {
		nn_incompatibleFuzzySetsException ex;
		throw ex;
	}
	switch (type) {
		case NN_TNORM_MINIMUM:
			while (!end_of_set()) {
				if (get_member() != op2.get_member()) {
					nn_incompatibleFuzzySetsException ex;
					throw ex;
				}
				if (get_membership() > op2.get_membership()) {
					result.add_new(get_member(), op2.get_membership());
				}
				else {
					result.add_new(get_member(), get_membership());
				}
				next_member();
				op2.next_member();
			}
			break;
		case NN_TNORM_PRODUCT:
				while (!end_of_set()) {
					if (get_member() != op2.get_member()) {
						nn_incompatibleFuzzySetsException ex;
						throw ex;
					}
					result.add_new(get_member(), get_membership() * op2.get_membership());
					next_member();
					op2.next_member();
				}
				break;
		case NN_TNORM_EINSTEIN_PRODUCT:
			while (!end_of_set()) {
				if (get_member() != op2.get_member()) {
					nn_incompatibleFuzzySetsException ex;
					throw ex;
				}
				result.add_new(get_member(), (get_membership() * op2.get_membership()) / (2 - ((get_membership() + op2.get_membership()) - get_membership() * op2.get_membership())));
				next_member();
				op2.next_member();
			}
			break;
		case NN_TNORM_DRASTIC_PRODUCT:
			while (!end_of_set()) {
				if (get_member() != op2.get_member()) {
					nn_incompatibleFuzzySetsException ex;
					throw ex;
				}
				if (op2.get_membership() == 1) {
					result.add_new(get_member(), get_membership());
				}
				else if (get_membership() == 1) {
					result.add_new(get_member(), op2.get_membership());
				}
				else {
					result.add_new(get_member(), 0.0);
				}
				next_member();
				op2.next_member();
			}
			break;

		default:
			break;
	}
	return result;
}

nn_fuzzy_set nn_fuzzy_set::s_norm(nn_fuzzy_set op2,int type = NN_SNORM_MAXIMUM) {
	nn_fuzzy_set result;
	reset_position();
	op2.reset_position();
	if (nn_size() != op2.nn_size()) {
		nn_incompatibleFuzzySetsException ex;
		throw ex;
	}
	switch (type) {
		case NN_SNORM_MAXIMUM:
			while (!end_of_set()) {
				if (get_member() != op2.get_member()) {
					nn_incompatibleFuzzySetsException ex;
					throw ex;
				}
				if (get_membership() < op2.get_membership()) {
					result.add_new(get_member(), op2.get_membership());
				}
				else {
					result.add_new(get_member(), get_membership());
				}
				next_member();
				op2.next_member();
			}
			break;
		case NN_SNORM_SUM:
			while (!end_of_set()) {
				if (get_member() != op2.get_member()) {
					nn_incompatibleFuzzySetsException ex;
					throw ex;
				}
				result.add_new(get_member(), get_membership() + op2.get_membership() - (get_membership() * op2.get_membership()));
				next_member();
				op2.next_member();
			}
			break;
		case NN_SNORM_EINSTEIN_SUM:
			while (!end_of_set()) {
				if (get_member() != op2.get_member()) {
					nn_incompatibleFuzzySetsException ex;
					throw ex;
				}
				result.add_new(get_member(), get_membership() + op2.get_membership() / (1 + (get_membership() * op2.get_membership())));
				next_member();
				op2.next_member();
			}
			break;		
		case NN_SNORM_DRASTIC_SUM:
			while (!end_of_set()) {
				if (get_member() != op2.get_member()) {
					nn_incompatibleFuzzySetsException ex;
					throw ex;
				}
				if (op2.get_membership() == 0) {
					result.add_new(get_member(), get_membership());
				}
				else if (get_membership() == 0) {
					result.add_new(get_member(), op2.get_membership());
				}
				else {
					result.add_new(get_member(), 1.0);
				}
				next_member();
				op2.next_member();
			}
			break;
		default:
			break;
	}
	return result;
}

nn_fuzzy_set nn_fuzzy_set::support() {
	nn_fuzzy_set result;
	reset_position();
	while (!end_of_set()) {
		if(get_membership() > 0)
			result.add_new(get_member(),get_membership());
		next_member();
	}
	return result;
}

nn_fuzzy_set nn_fuzzy_set::core() {
	nn_fuzzy_set result;
	reset_position();
	while (!end_of_set()) {
		if(get_membership() == 1)
			result.add_new(get_member(),get_membership());
		next_member();
	}
	return result;
}

bool nn_fuzzy_set::normal_set() {
	reset_position();
	while (!end_of_set()) {
		if(get_membership() == 1)
			return true;
		next_member();
	}
	return false;
}

nn_fuzzy_set nn_fuzzy_set::crossover() {
	nn_fuzzy_set result;
	reset_position();
	while (!end_of_set()) {
		if(get_membership() == 0.5)
			result.add_new(get_member(),get_membership());
		next_member();
	}
	return result;
}

nn_fuzzy_set nn_fuzzy_set::alpha_cut(double alpha) {
	nn_fuzzy_set result;
	reset_position();
	while (!end_of_set()) {
		if(get_membership() >= alpha)
			result.add_new(get_member(),get_membership());
		next_member();
	}
	return result;
}

nn_fuzzy_set nn_fuzzy_set::strong_alpha_cut(double alpha) {
	nn_fuzzy_set result;
	reset_position();
	while (!end_of_set()) {
		if(get_membership() > alpha)
			result.add_new(get_member(),get_membership());
		next_member();
	}
	return result;
}

bool is_convex(double lambda) {
//still not sure of what it exactly means!!
	return true;
}

/*bool is_symmetric(double point_of_symmetry) {
	reset_position();
	map<double,double>:: bidirectional_iterator itx;
	itx = set.find(point_of_symmetry);
	while (!end_of_set()) {
	}
}*/
nn_incompatibleFuzzySetsException::nn_incompatibleFuzzySetsException() {
	stmt = new char[100];
	stmt = "The Two or more Fuzzy sets are not compatible for the operator chosen";
}