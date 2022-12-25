#include "Martix.h"
#include "busChain.h"
#include "busRoute.h"
#include <iostream>

using namespace std;
const int N = 55;

bool st[N]; //标记数组
int pre[N]; //前驱
int routeNum; //公交线路数
double dis[N];
busRoute bus[10];
string platform[N]; //站点姓名
theMartix martix(30); //邻接矩阵

int getIndex(string plat_name); //寻找站点所对应的数字下标
void findMintime(); //寻找最少时间
void findMincost(); //寻找最少花费
void findMintransfer(); //寻找最少换乘次数

int main() { }

int getIndex(string plat_name)
{
    for (int i = 1; i <= routeNum; i++) {
        if (platform[i] == plat_name)
            return i;
    }
}
void findMintime()
{
    martix.init(); //初始化矩阵
    routeinfo ri;
    for (int i = 1; i <= routeNum; i++) {
        ri.Info = bus[i].getNum();
        busNode* p = bus[i].getLink().getFirst();
        for (p; p != NULL; p = p->next) {
            busNode* q = p->next;
            int ta = getIndex(p->plat_name);
            if (q != NULL) {
                int tb = getIndex(q->plat_name);
                ri.data = p->dx / bus[i].getSpeed(); //获得时间

                martix.Insert(ta, tb, i, ri);
                martix.Insert(tb, ta, i, ri);
            }
        }
    }
    cout << "输出出发站点和目的站点：\n";
    string pa, pb;
    cin >> pa >> pb;
    martix.Dijkstra(getIndex(pa), routeNum, dis, pre);
    if (dis[getIndex(pb)] == noEdge) {
        cout << "无法移动到" << pb << endl;
    } else {
        cout << "共花费" << dis[getIndex(pb)] << "分钟时间。\n";
    }
}

void findMincost() //最少花费
{
    martix.init(); //建立票价矩阵
    routeinfo ri;
    for (int i = 1; i <= routeNum; i++) {
        ri.Info = bus[i].getNum();
        ri.data = bus[i].getPrice(); //获得票价
        busNode* p = bus[i].getLink().getFirst();
        for (p; p != NULL; p = p->next) {
            busNode* q = p->next;
            int ta = getIndex(p->plat_name);
            if (q != NULL) {
                int tb = getIndex(q->plat_name);

                martix.Insert(ta, tb, i, ri);
                martix.Insert(tb, ta, i, ri);
            }
        }
    }
    cout << "输出出发站点和目的站点：\n";
    string pa, pb;
    cin >> pa >> pb;
    martix.Dijkstra(getIndex(pa), routeNum, dis, pre);
    if (dis[getIndex(pb)] == noEdge) {
        cout << "无法移动到" << pb << endl;
    } else {
        cout << "共花费" << dis[getIndex(pb)] << "元。\n";
    }
}
void findMintransfer() //最少换乘次数就是花最少的钱，因为票价相同，所以花最少的钱，换最少的班
{
    martix.init(); //建立票价矩阵
    routeinfo ri;
    for (int i = 1; i <= routeNum; i++) {
        ri.Info = bus[i].getNum();
        ri.data = bus[i].getPrice(); //获得票价
        busNode* p = bus[i].getLink().getFirst();
        for (p; p != NULL; p = p->next) {
            busNode* q = p->next;
            int ta = getIndex(p->plat_name);
            if (q != NULL) {
                int tb = getIndex(q->plat_name);

                martix.Insert(ta, tb, i, ri);
                martix.Insert(tb, ta, i, ri);
            }
        }
    }
    cout << "输出出发站点和目的站点：\n";
    string pa, pb;
    cin >> pa >> pb;
    martix.Dijkstra(getIndex(pa), routeNum, dis, pre);
    if (dis[getIndex(pb)] == noEdge) {
        cout << "无法移动到" << pb << endl;
    } else {
        cout << "共花费" << dis[getIndex(pb)] << "元。\n";
    }
}