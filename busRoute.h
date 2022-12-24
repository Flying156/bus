#ifndef busRoute_
#define busRoute_ //线路集合

#include "busChain.h"
#include <iostream>
#include <string>
using namespace std;

struct timeNode {
    int hour, minute, sec;
};
class busRoute {
    friend class busChain;

public:
    busRoute()
    {
        num = 0;
        speed = 0;
        price = 0;
        interval_time = 0;
    }
    void init1(int s, string n); //初始化，加站点
    void init2(timeNode a, timeNode b, double c); //加时间
    string getno() { return no; }
    int getNum() { return num; }
    int getPrice() { return price; }
    int getSpeed() { return speed; }
    busChain getLink() { return circuit; }
    double getInterval_time() { return interval_time; } //返回间隔时间
private:
    string no; //线路编号
    int num; //站点数量
    busChain circuit; //线路
    int speed; //车速
    int price; //价格
    timeNode begin_time; //起始时间
    timeNode end_time; //结束时间
    double interval_time; //间隔时间
};
void busRoute::init1(int s, string n)
{
    num = s;
    no = n;
    string a;
    double x, y;
    cout << "\t请依次输入站点名称与坐标\n";
    for (int i = 0; i < s; i++) {
        cin >> a >> x >> y;
        circuit.addNode(a, x, y);
    }
}
void busRoute::init2(timeNode a, timeNode b, double c)
{
    begin_time = a;
    end_time = b;
    interval_time = c;
}
#endif
#pragma once
