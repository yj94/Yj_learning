#include<iostream>
#include<list>
using namespace std;
/*
List��һ��˫����������ÿ���ڵ㶼����һ��Ԫ��ֵ������ָ�룬�ֱ�ָ��ǰһ���ڵ�ͺ�һ���ڵ㡣
���ڽڵ�֮��ͨ��ָ�����ӣ����list����������λ�ø�Ч�ز����ɾ��Ԫ�أ�ʱ�临�Ӷ�Ϊ��������ʹ��list�ǳ���������ҪƵ�������ɾ��Ԫ�صĳ�����

��vector��deque��ͬ��list��֧��������ʣ��޷�ͨ������ֱ�ӷ���Ԫ�ء�Ҫ����list�е�Ԫ�أ���Ҫ��ͷ�ڵ��β�ڵ㿪ʼ��������
����ܵ���list��ĳЩ���������ܽϲ��������ض�Ԫ�ص�ʱ�临�Ӷ�ΪO(n)��

���˸�Ч�Ĳ����ɾ��������list���ṩ������һЩ���ԣ���֧��������λ�ý���Ԫ�ؽ������ϲ���������list�ȡ�
���⣬list�������ڵ�����ʧЧ������½��в����ɾ����������Ϊ���Ľڵ�ͨ��ָ�����ӣ�������vector��deque�������ڴ����·���ʱʹ�õ�����ʧЧ��
*/

int main() {
	list<int> li1;
	li1.push_back(100);//β������
	li1.push_front(200);//ͷ������

	list<int>::iterator it;
	for (it = li1.begin(); it != li1.end(); it++) {
		cout<<"push " << *it << " ";
	}
	cout << endl;
	li1 = { 1,2,3,4,5 };
	li1.pop_back();
	li1.pop_front();
	
	li1.back() = 300;//β���޸�
	for (it = li1.begin(); it != li1.end(); it++) {
		cout<<"pop " << *it << " ";
	}
	cout << endl;
	
	list<int>::reverse_iterator rit;//˫������ķ��������
	for (rit = li1.rbegin(); rit != li1.rend(); rit++) {
		cout<<"���� " << *rit << " ";
	}
	cout << endl;


	system("pause");
	return 0;
}