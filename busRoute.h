#ifndef busRoute_
#define busRoute_ //��·����

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
    void init1(int s, string n); //��ʼ������վ��
    void init2(timeNode a, timeNode b, double c); //��ʱ��
    string getno() { return no; }
    int getNum() { return num; }
    int getPrice() { return price; }
    int getSpeed() { return speed; }
    busChain getLink() { return circuit; }
    double getInterval_time() { return interval_time; } //���ؼ��ʱ��
private:
    string no; //��·���
    int num; //վ������
    busChain circuit; //��·
    int speed; //����
    int price; //�۸�
    timeNode begin_time; //��ʼʱ��
    timeNode end_time; //����ʱ��
    double interval_time; //���ʱ��
};
void busRoute::init1(int s, string n)
{
    num = s;
    no = n;
    string a;
    double x, y;
    cout << "\t����������վ������������\n";
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
