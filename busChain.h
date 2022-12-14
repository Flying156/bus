#ifndef busChain_
#define busChain_//վ�㼯��

#include <iostream>
#include <string>
using namespace std;
struct busNode {
	string plat_name;//վ������
	double dx, dy;//����
	busNode *next;//��һվ��ָ��
};

class busChain {//һ·��վ��
	friend class busRoute;
	public:
		busChain() {
			firstNode = NULL;
			chainSize = 0;
		}//���캯��
		~busChain();
		busNode* getFirst() { return firstNode; }
		int getSize() { return chainSize; }
		void addNode(const string &s, const double &x, const double &y)//������վ��
		{
			if (firstNode != NULL) {
				busNode* p = firstNode;
				while (p) p = p->next;
				busNode* i = new busNode;
				i->plat_name = s;
				i->dx = x;
				i->dy = y;
				p->next = i;
				i->next = NULL;
			}
			else {
				firstNode->plat_name = s;
				firstNode->dx = x;
				firstNode->dy = y;
				firstNode->next = NULL;
			}
			chainSize++;
		}
		void getDist();//����վ�����
	private:
		busNode* firstNode;
		int chainSize;
};
busChain::~busChain() {
	busNode* p = firstNode, *q;
	while (p) {
		q = p->next;        
		delete p;
		p = q;
	}
}
void busChain::getDist() {

}
#endif
#pragma once