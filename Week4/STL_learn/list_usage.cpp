#include<iostream>
#include<list>
using namespace std;
/*
List是一个双向链表，它的每个节点都包含一个元素值和两个指针，分别指向前一个节点和后一个节点。
由于节点之间通过指针连接，因此list可以在任意位置高效地插入和删除元素，时间复杂度为常数。这使得list非常适用于需要频繁插入和删除元素的场景。

与vector和deque不同，list不支持随机访问，无法通过索引直接访问元素。要访问list中的元素，需要从头节点或尾节点开始遍历链表。
这可能导致list在某些操作上性能较差，例如查找特定元素的时间复杂度为O(n)。

除了高效的插入和删除操作，list还提供了其他一些特性，如支持在任意位置进行元素交换、合并两个有序list等。
此外，list还可以在迭代器失效的情况下进行插入和删除操作，因为它的节点通过指针连接，不会像vector和deque那样在内存重新分配时使得迭代器失效。
*/

int main() {
	list<int> li1;
	li1.push_back(100);//尾部插入
	li1.push_front(200);//头部插入

	list<int>::iterator it;
	for (it = li1.begin(); it != li1.end(); it++) {
		cout<<"push " << *it << " ";
	}
	cout << endl;
	li1 = { 1,2,3,4,5 };
	li1.pop_back();
	li1.pop_front();
	
	li1.back() = 300;//尾部修改
	for (it = li1.begin(); it != li1.end(); it++) {
		cout<<"pop " << *it << " ";
	}
	cout << endl;
	
	list<int>::reverse_iterator rit;//双向链表的反向迭代器
	for (rit = li1.rbegin(); rit != li1.rend(); rit++) {
		cout<<"反向 " << *rit << " ";
	}
	cout << endl;


	system("pause");
	return 0;
}