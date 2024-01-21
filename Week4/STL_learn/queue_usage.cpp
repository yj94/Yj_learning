#include <queue>
#include <iostream>
using namespace std;

int queue_usage() {
	queue<int>q1;
	q1.push(1);
	q1.push(2);
	q1.push(3);
	q1.push(4);
	while (!q1.empty()) {
		cout<<"q1 " << q1.front() << endl;
		q1.pop();
	}
	q1.push(1);
	q1.push(2);
	q1.push(3);
	q1.push(4);
	queue<int>q2(q1);
	while (!q2.empty()) {
		cout<<"q2 " << q2.front() << endl;
		q2.pop();
	}
	queue<int>q3=q1;
	q3.front()=0;
	q3.back() = 9;
	while (!q3.empty()) {
		cout<<"q3 " << q3.front() << endl;
		q3.pop();
	}
	cout << "ด๓ะก " << q3.size() << endl;
	return 0;
}