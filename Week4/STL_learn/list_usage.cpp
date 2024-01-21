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

int list_crud() {
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
	//带参数构造方法
	list<int>li2(3, 5);//(num,elem)
	list<int>::iterator itt;
	for (itt = li2.begin(); itt != li2.end(); itt++) {
		cout << "参数构造方法1 " << *itt << " ";
	}
	cout << endl;
	list<int>li3(li1.begin(), li1.end());//(beg,end) 不能使用+运算符 只能使用迭代器
	list<int>::iterator ittt;
	for (ittt = li3.begin(); ittt != li3.end(); ittt++) {
		cout << "参数构造方法2 " << *ittt << " ";
	}
	cout << endl;
	list<int>li4(li1);//(const &list)
	list<int>::iterator itttt;
	for (itttt = li4.begin(); itttt != li4.end(); itttt++) {
		cout << "参数构造方法3 " << *itttt << " ";
	}
	cout << endl;
	//list赋值 assgin,swap,insert
	//insert(pos,elem) ..(pos,n,elem) ..(pos,beg,end)
	//list大小 size()返回元素个数 resize()重定义容器长度 默认值填充 超出元素删除 empty()判断是否为空
	//list删除 clear()全部 erase(beg,end)左闭右开 erase(pos)返回删除位置的下一个位置 remove(elem)
	//list反序 reverse()

	system("pause");
	return 0;
}
int list_it() {
	list<int>li1(6, 6);//(num,elem)
	list<int>::iterator itt;
	li1.push_front(1);
	li1.push_back(9);
	for (itt = li1.begin(); itt != li1.end(); itt++) {
		cout << "li1元素 " << *itt << " ";
	}
	cout << endl;
	
	/*
	//报错
	for (itt = li1.begin(); itt != li1.end(); ) {
		if (*itt == 6) {
			li1.erase(itt);
		}
		else {
			itt++;
		}
	}
	cout << endl;
	*/
	//正确
	for (itt = li1.begin(); itt != li1.end(); ) {
		if (*itt == 6) {
			itt=li1.erase(itt);
		}
		else {
			itt++;
		}
	}
	for(itt = li1.begin(); itt != li1.end(); itt++) {
		cout << "删除后li1元素 " << *itt << " ";
	}
	cout << endl;
	cout << endl;
	system("pause");
	return 0;
}