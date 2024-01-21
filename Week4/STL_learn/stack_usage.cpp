#include <stack>
#include <iostream>
using namespace std;

int stack_usage() {
	stack<int> st1;//无迭代器 无法遍历
	st1.push(1);
	st1.push(2);
	st1.push(3);
	st1.push(4);
	while (!st1.empty()) {
		cout<<"st1 " << st1.top() << " ";
		st1.pop();
	}
	cout << endl;
	st1.push(1);
	st1.push(2);
	st1.push(3);
	st1.push(4);
	stack<int>st2(st1);//拷贝构造方法
	while (!st2.empty()) {
		cout<<"st2 " << st2.top() << " ";
		st2.pop();
	}
	cout << endl;
	stack<int>st3 = st1;//赋值
	while (!st3.empty()) {
		cout << "st3 " << st3.top() << " ";
		st3.pop();
	}
	cout << endl;
	cout<<"栈大小 " << st1.size() << endl;


	return 0;
}