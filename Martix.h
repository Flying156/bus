#ifndef Martix_
#define Martix_

#include "busRoute.h"
#include <cstring>
#include <iostream>

#define sn 30
const double noEdge = 99999;
using namespace std;
//两站点之间的线路信息
struct routeinfo {
    int Info; //线路编号
    double data; //数据
};
//两站点之间的线路信息，可有多条线路
struct Martix {
    routeinfo s[110];
};

class theMartix {
public:
    theMartix(int theCapacity); //构造函数

    void init(); //初始函数
    void Insert(int i, int j, int n, routeinfo ri); //插入新线路
    void outputPath(int pa, int pb, int l, string* platform, int* pre); //输出路径
    int Search(int i, int j, int cnt); //在两站点寻找最短的线路
    void Dijkstra(int b, int l, double* dis,
        int* pre); //查找b点到其余站点最短的距离和前置节点

private:
    Martix** mp;
    int n; //点数
    int m; //边数
};

theMartix::theMartix(int theCapacity) //构造函数
{
    n = theCapacity - 1;
    mp = new Martix*[theCapacity];
    for (int i = 0; i < theCapacity; i++)
        mp[i] = new Martix[theCapacity];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= n; k++)
                mp[i][j].s[k].data = noEdge;
}

//初始化
void theMartix::init()
{
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= sn; k++) {
                mp[i][j].s[k].data = noEdge; //
                mp[i][j].s[k].Info = 0;
            }
    }
}

//在两站点的第n处插入线路ri
void theMartix::Insert(int i, int j, int n, routeinfo ri)
{
    if (mp[i][j].s[n].data == noEdge) {
        mp[i][j].s[n] = ri;
        m++;
    } else
        mp[i][j].s[n] = ri;
}

//找出站点i到站点j的所有公交线路中的最优解
int theMartix::Search(int i, int j, int cnt)
{
    int k = 1;
    double sum = 1e9;
    for (int l = 1; l <= cnt; l++) {
        if (mp[i][j].s[l].data < sum) {
            sum = mp[i][j].s[l].data = sum;
            k = l;
        }
    }
    return k;
}

void theMartix::Dijkstra(int b, int l, double* dis, int* pre) //寻找一个站点到其他站点最短的距离
{
    bool st[50]; //标记数组
    memset(st, 0, sizeof st);
    for (int i = 1; i <= 26; i++) {
        dis[i] = mp[b][i].s[Search(b, i, l)].data;
        if (dis[i] == noEdge)
            pre[i] = 0;
        else
            pre[i] = b;
    }
    for (int i = 1; i <= 25; i++) {
        int t = -1;
        for (int j = 1; j <= 26; j++) {
            if (!st[j] && (t == -1 || dis[t] > dis[j])) {
                t = j;
            }
        }
        st[t] = 1;
        for (int j = 1; j <= 26; j++) {
            if (!st[j] && mp[t][j].s[Search(t, j, l)].data < noEdge) { //????????
                double tmp = dis[t] + mp[t][j].s[Search(t, j, l)].data;
                if (tmp < dis[j]) {
                    dis[j] = tmp;
                    pre[j] = t;
                }
            }
        }
    }
}

//输出路径
void theMartix::outputPath(int pa, int pb, int l, string* platform, int* pre)
{
    if (pa == pb)
        return;
    int tmp[sn]; //暂时存
    int cnt = 1;
    tmp[cnt] = pb;
    cnt++;
    int p = pre[pb];
    while (p != pa) {
        tmp[cnt++] = p;
        p = pre[p];
    }
    tmp[cnt] = pa;
    int info = mp[tmp[cnt]][tmp[cnt - 1]].s[Search(tmp[cnt], tmp[cnt - 1], l)].Info;
    for (int i = cnt; i > 0; i--) {
        if (i != 1) {
            if (mp[tmp[i]][tmp[i - 1]].s[Search(tmp[i], tmp[i - 1], l)].Info != info) {
                cout << "???" << platform[tmp[i]] << "??";
                cout << "??????��" << mp[tmp[i]][tmp[i - 1]].s[Search(tmp[i], tmp[i - 1], l)].Info << "??";
                cout << "???" << platform[tmp[i - 1]] << "??";
            } else {
                cout << "???" << platform[tmp[i]] << "??";
            }
            info = mp[tmp[i]][tmp[i - 1]].s[Search(tmp[i], tmp[i - 1], l)].Info; //??????��???
        } else //最后站点
            cout << "???" << platform[tmp[i]] << "??\n";
    }
}
#endif
#pragma once