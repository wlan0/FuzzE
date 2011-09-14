/*
 *  basic_defs.cpp
 *  open nn
 *
 *  Created by Sidhartha Mani on 07/09/11.
 *  Copyright 2011 Amrita School Of Engineering. All rights reserved.
 *
 */

#include "basic_defs.h"

fuzzy_set::fuzzy_set() { // default constructor
}

void fuzzy_set::add_new(double member, double membership_value) {
	fuzzy value;
	value.value = member;
	value.fuzz = membership_value;
	if( membership_value < 0 || membership_value > 1 ) {				//if membership values is out of bounds, throw exception
		illegalMembershipValueException e;
		throw(e);
	}
	set.push_back(value);
}

/*fuzzy_set::fuzzy_set(vector<fuzzy> v) { //convert a fuzzy vector into a fuzzy set object, the vector is lost in this operation
	while(v.size()>0) {
		set.push_back(v.back());
		v.pop_back();
	}
}*/

void fuzzy_set::print_set() {
	int i=0;
	if(set.size() == 0)
		return;
	cout<<"{";
	while (i<set.size()) {
		cout<<set.at(i++).fuzz<<"/"<<set.at(i).value;
		if(i==set.size())
		{
			cout<<"}\n";
			break;
		}
		cout<<",";
		}
}

void fuzzy_set::complement(int type = NN_COMPLEMENT_NORMAL, int parameter = 1) {
	int i=0;
	switch (type)
	{
		case(NN_COMPLEMENT_NORMAL):			// perform complement by the normal complement like in crisp sets
			while(i<set.size()) {
				set.at(i).fuzz = 1 - set.at(i).fuzz;
				i++;
			}
			break;
		case(NN_COMPLEMENT_SUGENOCLASS):			// perform complement by the sugeno class of operators
			while(i<set.size()) {
				set.at(i).fuzz = (1 - set.at(i).fuzz) / (1 + parameter * set.at(i).fuzz);
				i++;
			}
			break;
			
		default:
			break;
	}
}

fuzzy_set fuzzy_set::t_norm(fuzzy_set op2,int type = NN_TNORM_MINIMUM) {
	int i=0;
	fuzzy_set result;
	if(set.size() != op2.set.size())
	{
		incompatibleFuzzySetsException ex;
		throw ex;		
	}
	switch (type)
	{
		case NN_TNORM_MINIMUM:				//alias for fuzzy intersection operator
			while(i<set.size())
			{
				
				if(set.at(i).value != op2.set.at(i).value) {
					incompatibleFuzzySetsException ex;
					throw ex;
				}
				if(set.at(i).fuzz > op2.set.at(i).fuzz) {
					result.add_new(set.at(i).value,op2.set.at(i).fuzz);
				}
				else {
					result.add_new(set.at(i).value,set.at(i).fuzz);
				}
				i++;
			}
			break;
		case NN_TNORM_PRODUCT:				
			while(i<set.size())
			{
				
				if(set.at(i).value != op2.set.at(i).value) {
					incompatibleFuzzySetsException ex;
					throw ex;
				}
				result.add_new(set.at(i).value,set.at(i).fuzz * op2.set.at(i).fuzz);
				i++;
			}
			break;
		case NN_TNORM_EINSTEIN_PRODUCT:				
			while(i<set.size())
			{
				
				if(set.at(i).value != op2.set.at(i).value) {
					incompatibleFuzzySetsException ex;
					throw ex;
				}
				result.add_new(set.at(i).value,(set.at(i).fuzz * op2.set.at(i).fuzz)/(2-((set.at(i).fuzz + op2.set.at(i).fuzz)-(set.at(i).fuzz * op2.set.at(i).fuzz))));
				i++;
			}
			break;
		case NN_TNORM_DRASTIC_PRODUCT:				
			while(i<set.size())
			{
				
				if(set.at(i).value != op2.set.at(i).value) {
					incompatibleFuzzySetsException ex;
					throw ex;
				}
				if (set.at(i).value == 1) {
					result.add_new(set.at(i).value,op2.set.at(i).fuzz);
				}
				else if (op2.set.at(i).value == 1) {
					result.add_new(set.at(i).value,set.at(i).fuzz);
				}
				else {
					result.add_new(set.at(i).value,0.0);
				}

				i++;
			}
			break;
			
		default:
			break;
	}
	return result;
}

fuzzy_set fuzzy_set::s_norm(fuzzy_set op2,int type = NN_SNORM_MAXIMUM) {
	int i=0;
	fuzzy_set result;
	if(set.size() != op2.set.size())
	{
		incompatibleFuzzySetsException ex;
		throw ex;		
	}
	switch (type)
	{
		case NN_SNORM_MAXIMUM:				//alias for fuzzy union operator
			while(i<set.size())
			{
				
				if(set.at(i).value != op2.set.at(i).value) {
					incompatibleFuzzySetsException ex;
					throw ex;
				}
				if(set.at(i).fuzz < op2.set.at(i).fuzz) {
					result.add_new(set.at(i).value,op2.set.at(i).fuzz);
				}
				else {
					result.add_new(set.at(i).value,set.at(i).fuzz);
				}
				i++;
			}
			break;
			
		case NN_SNORM_SUM:				
			while(i<set.size())
			{
				
				if(set.at(i).value != op2.set.at(i).value) {
					incompatibleFuzzySetsException ex;
					throw ex;
				}
				result.add_new(set.at(i).value,(set.at(i).fuzz + op2.set.at(i).fuzz)-(set.at(i).fuzz * op2.set.at(i).fuzz));
				i++;
			}
			break;
			
		case NN_SNORM_EINSTEIN_SUM:				
			while(i<set.size())
			{
				
				if(set.at(i).value != op2.set.at(i).value) {
					incompatibleFuzzySetsException ex;
					throw ex;
				}
				result.add_new(set.at(i).value,(set.at(i).fuzz + op2.set.at(i).fuzz)/(1+set.at(i).fuzz * op2.set.at(i).fuzz));
				i++;
			}
			break;
			
		case NN_SNORM_DRASTIC_SUM:				
			while(i<set.size())
			{
								   
				if(set.at(i).value != op2.set.at(i).value) {
						incompatibleFuzzySetsException ex;
						throw ex;
				}
				if (set.at(i).value == 0) {
					result.add_new(set.at(i).value,op2.set.at(i).fuzz);
				}
				else if (op2.set.at(i).value == 0) {
					result.add_new(set.at(i).value,set.at(i).fuzz);
				}
				else {
					result.add_new(set.at(i).value,1.0);
			    }
				i++;
			}
			break;
			
		default:
			break;
	}
	return result;
}
							
fuzzy_set fuzzy_set::support() {
	fuzzy_set result;
	int i=0;
	while (i<set.size()) {
		if(set.at(i).fuzz > 0)
			result.add_new(set.at(i).value,set.at(i).fuzz);
		i++;
	}
	return result;
}
							  
fuzzy_set fuzzy_set::core() {
	fuzzy_set result;
	int i=0;
	while (i<set.size()) {
		if(set.at(i).fuzz == 1)
			result.add_new(set.at(i).value,set.at(i).fuzz);
		i++;
	}
	return result;
}
							   
bool fuzzy_set::normal_set() {
	int i=0;
	while(i<set.size()) {
		if(set.at(i).fuzz == 1)
			return true;
		i++;
	}
	return false;
}

fuzzy_set fuzzy_set::crossover() {
	fuzzy_set result;
	int i=0;
	while (i<set.size()) {
		if(set.at(i).fuzz == 0.5)
			result.add_new(set.at(i).value,set.at(i).fuzz);
		i++;
	}
	return result;
}
							   
fuzzy_set fuzzy_set::alpha_cut(double alpha) {
	fuzzy_set result;
	int i=0;
	while (i<set.size()) {
		if(set.at(i).fuzz >= alpha)
			result.add_new(set.at(i).value,set.at(i).fuzz);
		i++;
	}
	return result;
}
							   
fuzzy_set fuzzy_set::strong_alpha_cut(double alpha) {
	fuzzy_set result;
	int i=0;
	while (i<set.size()) {
		if(set.at(i).fuzz > alpha)
			result.add_new(set.at(i).value,set.at(i).fuzz);
		i++;
	}
	return result;
}
							   
							   
							   

	
