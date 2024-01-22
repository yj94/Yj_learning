#include <iostream>
#include <set>
using namespace std;

typedef int (*FUNC)(int, int);
int func_plus(int x, int y) {
	cout << "plus" << endl;
	return x + y;
}
int use_func(int x,int y,FUNC f) {
	return f(x, y);
}

class stu {
public:
	stu(int id, string name) {
		m_id = id;
		m_name = name;
	}
	int m_id;
	string m_name;
};
//Î±º¯Êý¶ÔÏó
class stu_asc {
public:
	bool operator()(const stu &s1,const stu &s2)const {
		return s1.m_id < s2.m_id;
	}
};
int func_usage() {
	cout << "equals " << use_func(3, 5, func_plus) << endl;
	set<stu, stu_asc> st_asc;
	set<stu, stu_asc>::iterator it;
	st_asc.insert(stu(5, "XiaoZhang"));
	st_asc.insert(stu(1, "XiaoMing"));
	st_asc.insert(stu(4, "XiaoWang"));
	st_asc.insert(stu(9, "LiSi"));
	st_asc.insert(stu(0, "Yuji"));
	for (it = st_asc.begin(); it != st_asc.end(); it++) {
		cout << it->stu::m_id << endl;
	}
	system("pause");
	return 0;
}