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

int list_crud() {
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
	//���������췽��
	list<int>li2(3, 5);//(num,elem)
	list<int>::iterator itt;
	for (itt = li2.begin(); itt != li2.end(); itt++) {
		cout << "�������췽��1 " << *itt << " ";
	}
	cout << endl;
	list<int>li3(li1.begin(), li1.end());//(beg,end) ����ʹ��+����� ֻ��ʹ�õ�����
	list<int>::iterator ittt;
	for (ittt = li3.begin(); ittt != li3.end(); ittt++) {
		cout << "�������췽��2 " << *ittt << " ";
	}
	cout << endl;
	list<int>li4(li1);//(const &list)
	list<int>::iterator itttt;
	for (itttt = li4.begin(); itttt != li4.end(); itttt++) {
		cout << "�������췽��3 " << *itttt << " ";
	}
	cout << endl;
	//list��ֵ assgin,swap,insert
	//insert(pos,elem) ..(pos,n,elem) ..(pos,beg,end)
	//list��С size()����Ԫ�ظ��� resize()�ض����������� Ĭ��ֵ��� ����Ԫ��ɾ�� empty()�ж��Ƿ�Ϊ��
	//listɾ�� clear()ȫ�� erase(beg,end)����ҿ� erase(pos)����ɾ��λ�õ���һ��λ�� remove(elem)
	//list���� reverse()

	system("pause");
	return 0;
}
int list_it() {
	list<int>li1(6, 6);//(num,elem)
	list<int>::iterator itt;
	li1.push_front(1);
	li1.push_back(9);
	for (itt = li1.begin(); itt != li1.end(); itt++) {
		cout << "li1Ԫ�� " << *itt << " ";
	}
	cout << endl;
	
	/*
	//����
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
	//��ȷ
	for (itt = li1.begin(); itt != li1.end(); ) {
		if (*itt == 6) {
			itt=li1.erase(itt);
		}
		else {
			itt++;
		}
	}
	for(itt = li1.begin(); itt != li1.end(); itt++) {
		cout << "ɾ����li1Ԫ�� " << *itt << " ";
	}
	cout << endl;
	cout << endl;
	system("pause");
	return 0;
}