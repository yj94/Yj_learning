#include <set>
#include <iostream>
using namespace std;

int main() {
	set<int> st1;
	multiset<int> mst1;
	//insert(elem) begin end rbegin rend
	st1.insert(233);
	st1.insert(223);
	st1.insert(222);
	set<int>::iterator it;
	set<int>::reverse_iterator rit;
	for (it = st1.begin(); it != st1.end(); it++) {
		cout << "st1 " << *it << endl;
	}
	for (rit = st1.rbegin(); rit != st1.rend(); rit++) {
		cout << "rst1 " << *rit << endl;
	}
	set<int> st2(st1);
	set<int> st3=st1;
	set<int> st4 = {2,3,3,4};
	st4.swap(st1);
	for (it = st2.begin(); it != st2.end(); it++) {
		cout << "st2 " << *it << endl;
	}
	for (it = st3.begin(); it != st3.end(); it++) {
		cout << "st3 " << *it << endl;
	}
	for (it = st4.begin(); it != st4.end(); it++) {
		cout << "st4 " << *it << endl;
	}
	for (it = st1.begin(); it != st1.end(); it++) {
		cout << "st1 " << *it << endl;
	}
	//É¾³ı
	for (it = st1.begin(); it != st1.end();) {
		if (*it == 3) {
			it=st1.erase(it);
		}
		else {
			it++;
		}
	}
	for (it = st1.begin(); it != st1.end(); it++) {
		cout << "É¾³ıºóst1 " << *it << endl;
	}
	return 0;
}