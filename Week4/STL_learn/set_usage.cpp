#include <set>
#include <iostream>
using namespace std;

int set_usage() {
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
	//删除
	for (it = st1.begin(); it != st1.end();) {
		if (*it == 3) {
			it=st1.erase(it);
		}
		else {
			it++;
		}
	}
	for (it = st1.begin(); it != st1.end(); it++) {
		cout << "删除后st1 " << *it << endl;
	}
	//升序降序
	set<int, less<int>> st_asc;//类作为函数对象使用
	set<int, greater<int>> st_desc;
	st_asc.insert(1);
	st_asc.insert(9);
	st_asc.insert(3);
	st_desc.insert(1);
	st_desc.insert(9);
	st_desc.insert(3);
	for (it = st_asc.begin(); it != st_asc.end(); it++) {
		cout << "st_asc " << *it << endl;
	}
	for (it = st_desc.begin(); it != st_desc.end(); it++) {
		cout << "st_desc " << *it << endl;
	}
	//查找
	it = st_asc.find(3);//find(elem) ret elem 未找到会返回 容器end
	if (it == st_asc.end()) {
		cout << "未找到" << endl;
	}
	else {
		cout<<"找到3 " << *it << endl;
	}
	//计数 返回0,1 可用于 查找 对于mutiset 可返回>1的值
	int st1_count=st_desc.count(1);
	cout<<"是否找到" << st1_count << endl;
	//返回元素迭代器
	set<int> set_list{ 1,3,0,4,5,7,8,2,9 };
	set<int>::iterator it1;
	set<int>::iterator it2; 
	it1 = set_list.lower_bound(5);
	it2 = set_list.upper_bound(5);
	cout<<"第一个大于等于5 " << *it1 << endl;
	cout<<"第一个大于5 " << *it2 << endl;
	//equal_range(elem) 返回两个迭代器
	pair<set<int>::iterator, set<int>::iterator> p1 = set_list.equal_range(5);
	if (p1.first == set_list.end() && p1.second == set_list.end()) {
		cout << "未找到" << endl;
	}
	else {
		cout << "对组 " << *p1.first<<" and "<<*p1.second << endl;
	}
	
	return 0;
}