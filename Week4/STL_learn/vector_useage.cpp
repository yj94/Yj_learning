#include <vector>
#include <iostream>
using namespace std;

int vec() {
	int arr[] = { 1,2,3,4,5 };
	vector<int> v1( arr,arr + 5 );//����ָ�븳ֵ ����ҿ� ����洢v1
	vector<int> v2( 3,5 );//�洢3��5
	for (int i = 0; i < 3; i++) {
		cout <<"���鸳ֵ " << v2[i] << " ";
	}
	cout << endl;

	vector<int>vIa, vIb, vIc, vId;
	vIa.assign(arr, arr + 5);//ָ�븳ֵ �Ḳ��
	for (int i = 0; i < vIa.size(); i++) {
		cout <<"ָ�븳ֵ " << vIa[i] << " ";
	}
	cout << endl;
	vIb.assign(vIa.begin(), vIa.end());//vec����
	for (int i = 0; i < vIb.size(); i++) {
		cout <<"������ֵ " << vIb[i] << " ";
	}
	cout << endl;
	vIc.assign(vIa.begin() + 2, vIa.end() - 1);//vec���� ����ѡȡ
	for (int i = 0; i < vIc.size(); i++) {
		cout <<"�������� " << vIc[i] << " ";
	}
	cout << endl;

	vIb.swap(vIc);
	for (int i = 0; i < vIb.size(); i++) {
		cout <<"��������b " << vIb[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < vIc.size(); i++) {
		cout <<"��������c " << vIc[i] << " ";
	}
	cout << endl;
	//size() resize() empty()  

	vId.assign(arr, arr + 5);
	//vIc.at(8) = 666;//at��������ʾ Խ���쳣  std::out_of_range

	//push_back pop_back
	vId.push_back(999); //β������
	vId.pop_back();	//β��ɾ��
	vId.insert(vId.begin()+2,100); //���� ��һ������Ϊvecָ�� ���ҷ��ز����ֵ����λ��
	vId.insert(vId.begin() + 3, 5, 200); //���� ָ�� ���� ֵ ������
	vId.insert(vId.end(), vId.begin(),vId.end()); //����ָ������ ������
	for (int i = 0; i < vId.size(); i++) {
		cout<< "���� " << vId[i] << " ";//��Խ����ֱ���˳�
	}
	cout << endl;
	return 0;
}
int vec_it() {
	//��������ʹ��
	int arr[] = { 1,2,3,4,5 };
	vector<int>vIa, vIb, vIc, vId;
	vIa.assign(arr,arr+5);
	vector<int>::iterator ita;
	for (ita = vIa.begin(); ita != vIa.end(); ita++) {
		cout << *ita << " ";
	}
	cout<< endl;

	//��ָ������ ������ʧЧ
	vector<int>::iterator itb=vIa.begin()+3;
	cout <<"������vIa+3 " << *itb << endl;
	//�����ʹ�õ��������ֿ�ָ��
	vIa.insert(itb, 8);
	//Ӧ�����¸�ֵ������
	itb = vIa.begin() + 3;
	cout<<"���������¸�ֵ��vIa+3 " << *itb << endl;
	
	vIb = { 1,2,3,3,3,3,4,5 };
	vector<int>::iterator itc;
	for (itc = vIb.begin(); itc != vIb.end();) { //����������forѭ���� �ᵼ�·��ʵ���erase��Ԫ�صĿ�ָ��
		if (*itc == 3) {
			itc = vIb.erase(itc);
		}
		else {
			cout << *itc << endl;
			++itc;
		}
	}
	//����ʹ���µ������洢erase������� ���ܻ���Ϊ�������϶�������ʧЧ�����µ�����ʧЧ
	//���߽�ָ�����
	for (itc = vIb.begin(); itc != vIb.end();itc++) { //����������forѭ���� �ᵼ�·��ʵ���erase��Ԫ�صĿ�ָ��
		if (*itc == 3) {
			itc = vIb.erase(itc);
			itc--;
		}
		cout << *itc << endl;
	}

	return 0;
}