
#ifndef busRoute_
#define busRoute_

#include "busChain.h"
#include <iostream>
using namespace std;

class busRoute {
public:
	busRoute() {
		num = 0;
		sum = 0;
		speed = 0;
		price = 0;
		time_ = 0;
	}
	~busRoute();
	
	void initi1(int nn, int ss);//设置线路编号、站点总数 
	void initi2(double sp, double pp, double tt);//设置票价、发车间隔、速度
	double getPrice() { return price; }
	double getSpeed() { return speed; }
	int getNum() { return num; }
	int getSum() { return sum; }
	double getTime_() { return time_; }
	busChain& getLink() { return link; }
	
	int num;//线路编号 
	int sum;//站点总数 
	double speed;//速度 
	double price;//票价 
	double time_;//发车时间间隔
	busChain link;//本公交线路链表 
	
};


void busRoute::initi1(int nn, int ss) {
	num = nn;
	sum = ss;
	string str;
	double xx, yy;
	cout << "请依次输入各个站点的名称和坐标，均以空格分隔：" << endl;
	for (int i = 1; i <= sum; i++) {
		cout << "\t站点" << i << "：";
		
		cin >> str >> xx >> yy;
		link.insert(str, xx, yy);
	}
	
}

//sp表示价格，pp表示发车间隔，tt表示速度
void busRoute::initi2(double sp, double pp, double tt) {
	price = sp;
	time_ = pp;
	speed = tt;
	
}

#endif
#pragma once
