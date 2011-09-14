#include "nn.h"

int main (int argc, char * const argv[]) {
	try { 
		nn_fuzzy_set set1,set2,set3;
		set1.add_new(1, 0.5);
		set1.add_new(2, 0.6);
		set1.print_set();
		set1.erase(2);
		set1.add_new(3, 0.865);
		set1.print_set();
		vector<double> result;
		vector<double>:: iterator it;
		result = set1.get_members();
		it = result.begin();
		while (it!=result.end()) {
			cout<<*it<<" ";
			it++;
		}
		cout<<"\n";
		set1.print_set();
		set1.complement(2,2);
		set1.print_set();
		set1.add_new(1, 0.76);
		set1.print_set();
		set2.add_new(1, 0.45);
		set2.add_new(3, 0.65);
		set2.print_set();
		set3 = set1.t_norm(set2, 2);
		set3.print_set();
		set3 = set1.s_norm(set2, 1);
		set3.print_set();
	}
	catch(nn_illegalMembershipValueException ex)	//caught whenever an exception is thrown because of membership values out of bounds is trying to be assigned
	{
		ex.statement();
	}
	catch (nn_incompatibleFuzzySetsException ex) {  //caught whenever two incompatible fuzzy sets are used as operations for some fuzzy operation
		ex.statement();
	}
	catch (nn_noMoreElementsException ex) {  //caught whenever you try to perform set operations after all the elements have been processed, and the current pointer is pointing to the end of the set
		ex.statement();
	}
	return 0;
		
}
