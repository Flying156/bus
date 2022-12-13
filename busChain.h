#ifndef busChain_
#define busChain_//站点集合

#include <iostream>
#include <string>

struct busNode {
	string plat_name;//站点名称
	double dx, dy;//坐标
	busNode* next;//下一站点指针
};

class busChain {//一路的站点
	friend busNode;
	public:
		busChain() {
			firstNode = NULL;
			chainSize = 0;
		}//构造函数
		~busChain();
		busNode* getFirst() { return firstNode; }
		int getSize() { return chainSize; }
		void addNode(string name, double x, double y);//插入新节点
		void getDist() {};//计算站点距离
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
void busChain::addNode(string name, double x, double y) {
	if (firstNode != NULL) {
		busNode* p = firstNode;
		while (p) p = p->next;
		busNode* i = new busNode;
		i->plat_name = name;
		i->dx = x;
		i->dy = y;
		p->next = i;
		i->next = NULL;
	}
	else {
		firstNode->plat_name = name;
		firstNode->dx = x;
		firstNode->dy = y;
		firstNode->next = i;
	}
	chainSize++;
}
void busChain::getDist() {

}