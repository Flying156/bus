#ifndef busChain_
#define busChain_//站点集合

#include <iostream>
#include <string>
using namespace std;
struct busNode {
	string plat_name;//站点名称
	double dx, dy;//坐标
	busNode *next;//下一站点指针
};

class busChain {//一路的站点
	friend class busRoute;
	public:
		busChain() {
			firstNode = NULL;
			chainSize = 0;
		}//构造函数
		~busChain();
		busNode* getFirst() { return firstNode; }
		int getSize() { return chainSize; }
		void addNode(const string &s, const double &x, const double &y)//增加新站点
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
		void getDist();//计算站点距离
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