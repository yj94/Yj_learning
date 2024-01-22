#include <map>
#include <iostream>
using namespace std;
class stu {
public:
	stu() {};
	stu(int id, string name) {
		this->id = id;
		this -> name = name;
	};
	int id;
	string name;
	friend ostream& operator<<(ostream& os, const stu& s1) {//友元函数 重载输出运算符
		return os << "id: " << s1.id << " name: " << s1.name;
	}
};
int map_usage() {
	map<int, string> m1;
	map<int,stu> m2;
	map<int, string>::iterator it;
	m1 = { {0,"Apple"},{1,"Orange"} };
	//增
	m1.insert(pair<int, string>(9, "Figs"));
	m1.insert(map<int, string>::value_type(8, "Fish"));
	int idd = 5;
	string namen = "pig";
	pair<int, string>p1(idd, namen);
	m1.insert(p1);
	m1[2] = "Banana";
	m1.erase(0);
	it = m1.find(8);
	for (auto p1 : m1) {
		cout<<"m1 " << p1.first << " " << p1.second << endl;
	}
	cout << "m1 size " << m1.size() << endl;
	if (it == m1.end()) {
		cout << "not found" << endl;
	}
	else {
		cout << "find m1 8 " << it->first<<" "<<it->second << endl;
	}
	
	//对象的添加
	stu s1(10, "Beef");
	stu s2(11, "Bacon");
	stu s3(12, "Duck");
	stu s4(12, "Swan");
	m2.insert(pair<int, stu>(static_cast<int>(s1.id), s1));
	m2.insert(map<int, stu>::value_type(s2.id, s2));
	m2.insert(map<int, stu>::value_type(s2.id, s4));//不会覆盖原k:v
	m2[s3.id] = s3;
	for (auto p2 : m2) {
		cout << "m2 " << p2.first << " " << p2.second.name << endl;
	}
	map<int, stu>::iterator itt;
	for (itt = m2.begin(); itt != m2.end(); itt++) {
		pair<int, stu> p = *itt;
		int key = p.first;
		stu v = p.second;
		cout << v << endl;
	}
	system("pause");
	return 0;
}