#ifndef busRoute_
#define busRoute_//��·����

#include "busChain.h"
#include <iostream>
using namespace std;
struct timeNode {
	int hour, minute, sec;
};
class busRoute {
	friend timeNode;
	public:
		busRoute() {
			size = 0;
			speed = 0;
			price = 0;
			interval_time = 0;
		}
		void init1(int s, string n);//��ʼ������վ��
		void init2(timeNode a, timeNode b, double c);//��ʱ��
		string getno() { return no; }
		int getspeed() { return speed; }
		double getinterval_time{ return interval_time; }
	private:
		string no;//��·���
		int size;//վ������
		busNode circuit;//��·
		int speed;//����
		int price;//�۸�
		timeNode begin_time;//��ʼʱ��
		timeNode end_time;//����ʱ��
		double interval_time;//���ʱ��
};
void busRote::init1(int s, string n) {
	size = s;
	no = n;
	string a;
	double x, y;
	cout << "\t����������վ������������\n";
	for (int i = 0; i < s; i++) {
		cin >> a >> x >> y;
		circuit.addNode(a, x, y);
	}
}
void busRote::init2(timeNode a, timeNode b, double c) {
	begin_time = a;
	end_time = b;
	interval_time = c;
}

