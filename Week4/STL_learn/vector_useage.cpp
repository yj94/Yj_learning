#include <vector>
#include <iostream>
using namespace std;

int vec() {
	int arr[] = { 1,2,3,4,5 };
	vector<int> v1( arr,arr + 5 );//数组指针赋值 左闭右开 区间存储v1
	vector<int> v2( 3,5 );//存储3个5
	for (int i = 0; i < 3; i++) {
		cout <<"数组赋值 " << v2[i] << " ";
	}
	cout << endl;

	vector<int>vIa, vIb, vIc, vId;
	vIa.assign(arr, arr + 5);//指针赋值 会覆盖
	for (int i = 0; i < vIa.size(); i++) {
		cout <<"指针赋值 " << vIa[i] << " ";
	}
	cout << endl;
	vIb.assign(vIa.begin(), vIa.end());//vec容器
	for (int i = 0; i < vIb.size(); i++) {
		cout <<"容器赋值 " << vIb[i] << " ";
	}
	cout << endl;
	vIc.assign(vIa.begin() + 2, vIa.end() - 1);//vec容器 区间选取
	for (int i = 0; i < vIc.size(); i++) {
		cout <<"容器区间 " << vIc[i] << " ";
	}
	cout << endl;

	vIb.swap(vIc);
	for (int i = 0; i < vIb.size(); i++) {
		cout <<"容器交换b " << vIb[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < vIc.size(); i++) {
		cout <<"容器交换c " << vIc[i] << " ";
	}
	cout << endl;
	//size() resize() empty()  

	vId.assign(arr, arr + 5);
	//vIc.at(8) = 666;//at函数可显示 越界异常  std::out_of_range

	//push_back pop_back
	vId.push_back(999); //尾部插入
	vId.pop_back();	//尾部删除
	vId.insert(vId.begin()+2,100); //插入 第一个参数为vec指针 并且返回插入的值所在位置
	vId.insert(vId.begin() + 3, 5, 200); //插入 指针 个数 值 不返回
	vId.insert(vId.end(), vId.begin(),vId.end()); //插入指针区间 不返回
	for (int i = 0; i < vId.size(); i++) {
		cout<< "访问 " << vId[i] << " ";//若越界则直接退出
	}
	cout << endl;
	return 0;
}
int vec_it() {
	//迭代器的使用
	int arr[] = { 1,2,3,4,5 };
	vector<int>vIa, vIb, vIc, vId;
	vIa.assign(arr,arr+5);
	vector<int>::iterator ita;
	for (ita = vIa.begin(); ita != vIa.end(); ita++) {
		cout << *ita << " ";
	}
	cout<< endl;

	//空指针问题 迭代器失效
	vector<int>::iterator itb=vIa.begin()+3;
	cout <<"迭代器vIa+3 " << *itb << endl;
	//插入后使用迭代器出现空指针
	vIa.insert(itb, 8);
	//应该重新赋值迭代器
	itb = vIa.begin() + 3;
	cout<<"迭代器重新赋值后vIa+3 " << *itb << endl;
	
	vIb = { 1,2,3,3,3,3,4,5 };
	vector<int>::iterator itc;
	for (itc = vIb.begin(); itc != vIb.end();) { //若自增放在for循环中 会导致访问到被erase的元素的空指针
		if (*itc == 3) {
			itc = vIb.erase(itc);
		}
		else {
			cout << *itc << endl;
			++itc;
		}
	}
	//或者使用新迭代器存储erase后的容器 可能会因为编译器认定迭代器失效导致新迭代器失效
	//或者将指针后移
	for (itc = vIb.begin(); itc != vIb.end();itc++) { //若自增放在for循环中 会导致访问到被erase的元素的空指针
		if (*itc == 3) {
			itc = vIb.erase(itc);
			itc--;
		}
		cout << *itc << endl;
	}

	return 0;
}