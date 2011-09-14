/*
 *  nn_fuzzy.cpp
 *  open nn
 *
 *  Created by Sidhartha Mani on 08/09/11.
 *  Copyright 2011 Amrita School Of Engineering. All rights reserved.
 *
 */

#include "nn_fuzzy.h"

nn_fuzzy::nn_fuzzy() {
	it = set.begin();
}

void nn_fuzzy::add_new(double member,double membership_value) {
	if (membership_value > 1 || membership_value < 0) {
		nn_illegalMembershipValueException ex;
		throw ex;
	}
	set[member] = membership_value;
}

void nn_fuzzy::print_set() {
	map<double,double>::iterator itx;
	itx = set.begin();
	if (itx==set.end()) {
		return;
	}
	cout<<"{";
	while (itx!=set.end()) {
		cout << itx->second << "/" << itx->first; 
		itx++;
		if(itx==set.end()) {
			cout<<"}\n";
			return;
		}
		cout << ",";
	}
}
	
double nn_fuzzy::get_membership_value(double member) {
	if (set.find(member) != set.end()) {
		return set[member];
	}
	return NULL;
}

vector<double> nn_fuzzy::get_members() {
	map<double,double>::iterator itx;
	vector<double> result;
	itx=set.begin();
	while (itx!=set.end()) {
		result.push_back(itx->first);
		itx++;
	}
	return result;
}

void nn_fuzzy::erase(double member) {
	set.erase(member);
}

void nn_fuzzy::clear_all() {
	set.clear();
}

bool nn_fuzzy::is_normal_set() {
	map<double,double>::iterator itx;
	itx = set.begin();
	while (itx!=set.end()) {
		if (itx->second == 1) {
			return true;
		}
		itx++;
	}
	return false;
}

bool nn_fuzzy::end_of_set() {
	if (it==set.end()) {
		return true;
	}
	return false;
}

bool nn_fuzzy::set_membership(double membership) {
	if (membership > 1 || membership < 0) {
		nn_illegalMembershipValueException ex;
		throw ex;
	}
	if (it!=set.end()) {
		set[it->first] = membership;
		return true;
	}
	return false;
}

bool nn_fuzzy::set_membership(double member,double membership) {
	if (membership > 1 || membership < 0) {
		nn_illegalMembershipValueException ex;
		throw ex;
	}
	if (set.find(member)!=set.end()) {
		set[member] = membership;
		return true;
	}
	return false;
}

double nn_fuzzy::get_member() {
	if(it!=set.end()) {
		return it->first;
	}
	return NULL;
}

double nn_fuzzy::get_membership() {
	if (it!=set.end()) {
		return it->second;
	}
	return NULL;
}

void nn_fuzzy::next_member() {
	if (it!=set.end()) {
		it++;
		return;
	}
	nn_noMoreElementsException ex;
	throw ex;
}

void nn_fuzzy::reset_position() {
	it = set.begin();
}

size_t nn_fuzzy::nn_size() {
	return set.size();
}

nn_illegalMembershipValueException::nn_illegalMembershipValueException() {
	stmt = new char[100];
    stmt = "The membership value does not lie between 0 and 1, inclusive";
}

nn_noMoreElementsException::nn_noMoreElementsException() {
	stmt = new char[100];
    stmt = "Trying to perform fuzzy operation on non existant value, you have already traversed through the entire set";
}
	