#include<deque>
#include<iostream>
using namespace std;
int deq() {
	//deque 和 vector 区别 一个双端 一个单端
	//如果需要在中间位置频繁增加/移除元素，则推荐使用deque，否则使用vector
	//新增两个函数 push_front pop_front

	deque<int> de1 = { 1,2,3,4,5 };
	de1.push_front(100);
	deque<int>::iterator it;
	for (it = de1.begin(); it != de1.end(); it++) {
		cout << *it << " ";
		
	}
	cout << endl;
	de1.pop_front();//效果同erase
	for (it = de1.begin(); it != de1.end(); it++) {
		cout << *it << " ";
		
	}
	cout << endl;
	de1.erase(de1.begin());
	for (it = de1.begin(); it != de1.end(); it++) {
		cout << *it << " ";
		
	}
	cout << endl;
	system("pause");

	/*
	Vector（向量）是一个动态数组，它以连续的内存块存储元素。
	它支持随机访问（通过索引访问元素）和动态增长。当元素数量超过当前分配的内存空间时，vector会自动重新分配更大的内存块，并将元素复制到新的内存中。这可能会导致插入和删除操作的时间复杂度较高，因为需要移动其他元素。
	然而，由于元素在内存中连续存储，vector对于需要频繁访问元素的场景非常高效。

	Deque（双端队列）是一个双端序列，它允许在序列的两端进行高效的插入和删除操作。
	deque的内部实现通常使用了一系列的缓冲区，每个缓冲区存储若干个元素，并通过指针进行连接。这使得deque可以在两端进行快速的插入和删除操作，时间复杂度为常数。
	与vector不同的是，deque不要求元素在内存中连续存储，因此在插入和删除元素时不需要移动其他元素。然而，与vector相比，deque的随机访问性能较差。

	总结而言，vector适用于需要频繁访问元素的场景，而deque适用于需要在两端进行高效插入和删除操作的场景。选择使用哪个容器取决于具体的使用需求。
	*/
	return 0;
}