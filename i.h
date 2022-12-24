#ifndef adjMatrix_
#define adjMatrix_

#include<iostream>
#include<stack> 
#include<string.h>
#include "busRoute.h"
#define sn 30
//#define bn 100
#define noEdge 9999
using namespace std;

//两站点之间的线路信息
struct routeInfo {
	int Info;//线路编号 
	double data;//数据 
};

//两站点之间的线路信息，可有多条线路
struct ver {
	routeInfo ro[sn];//每条线路信息 
};

class adjMatrix {
public:
	adjMatrix(int theCapacity);//构造函数
	~adjMatrix();//析构函数

	void insert(int i, int j, int nth, routeInfo rt);//插入元素
	void erase(int i, int j, int nth);//删除元素 
	double getElement(int i, int j, int nth);//查找 
	int getM() const {//得到总边数
		return m;
	}
	void ini();//初始化为无边
	int search(int i, int j, int su);//查找站点i到站点j的所有线路中的最优解
	int search2(int i, int j, int su, busRoute* bus);//查找站点i到站点j的所有线路中的最优解（判断是否加入等待时间）
	void Dijkstra(double* dis, int* pre, int da, int su);//求da到其他点的最短路径
	void outputPath(int pa, int pb, string* in, int* pre, int su);//输出pa到pb的最短线路
	void Dijkstra2(double* dis, int* pre, int da, int su, busRoute* bus); //求da到其他点的最短路径，加入中间站点的等待时间
	double find_(int Infomation, int su, busRoute* bus);//查找线路编号对应的等待时间

private:
	ver** theMatrix;//邻接矩阵
	int n;//点数 
	int m;//边数 

};

adjMatrix::adjMatrix(int theCapacity) {
	n = theCapacity - 1;
	theMatrix = new ver * [theCapacity];
	for (int i = 0; i < theCapacity; i++) {
		theMatrix[i] = new ver[theCapacity];
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			for (int k = 1; k <= sn; k++) {
				theMatrix[i][j].ro[k].data = noEdge;
			}

		}
	}
	m = 0;
}

adjMatrix::~adjMatrix() {
	for (int i = 0; i < n; i++) {
		delete[] theMatrix[i];
	}
	delete[] theMatrix;
	m = 0;//边数
	n = 0;//点数
}

void adjMatrix::insert(int i, int j, int nth, routeInfo rt) {//在i-j处的第nth条线路信息中插入rt
	if (theMatrix[i][j].ro[nth].data == noEdge) {
		theMatrix[i][j].ro[nth] = rt;
		m++;//边数 
	}
	else {//已有边，更新信息
		theMatrix[i][j].ro[nth] = rt;
	}

}

void adjMatrix::erase(int i, int j, int nth) {//删除i-j处的第nth条线路的边
	if (theMatrix[i][j].ro[nth].data == noEdge) {
		cout << "Error!" << endl;
	}
	else {
		theMatrix[i][j].ro[nth].data = noEdge;
		m--;//边数
	}
}

double adjMatrix::getElement(int i, int j, int nth) {//得到i-j处的第nth条线路的边值
	return theMatrix[i][j].ro[nth].data;
}


void adjMatrix::ini() {//初始化均为无边，线路编号均为0 
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			for (int k = 1; k <= sn; k++) {
				theMatrix[i][j].ro[k].data = noEdge;
				theMatrix[i][j].ro[k].Info = 0;
			}

		}
	}
}

//求da到其他所有点的最短路径长度
void adjMatrix::Dijkstra(double* dis, int* pre, int da, int su) {
	int* vis = new int[30];//标记数组
	//memset(&vis, 0, 30);
	for (int i = 1; i <= n; i++) {//初始化为未访问过
		vis[i] = 0;
	}
	for (int i = 1; i <= 26; i++) {
		dis[i] = theMatrix[da][i].ro[search(da, i, su)].data;
		//cout<<"测试："<<this->search(da,i,su)<<" "<<dis[i]<<endl;
		if (dis[i] == noEdge)
			pre[i] = 0;
		else
			pre[i] = da;
	}
	dis[da] = 0;//da到da距离为0 
	/*for(int i=1;i<=8;i++) {
		cout<<i<<" "<<dis[i]<<endl;
	}
	cout<<endl;*/
	vis[da] = 1;//标记为访问过 

	for (int i = 1; i <= 25; i++) {
		double temp = noEdge;
		int v = 0;
		for (int j = 1; j <= 26; j++) {//找出距离 点集 最近的点 
			if (vis[j] == 0 && dis[j] < temp) {
				//cout << j << endl;
				v = j;
				temp = dis[j];
			}
		}
		vis[v] = 1;
		for (int j = 1; j <= 26; j++) {
			if (vis[j] == 0 && theMatrix[v][j].ro[search(v, j, su)].data < noEdge) {//更新 
				double dd = dis[v] + theMatrix[v][j].ro[search(v, j, su)].data;
				if (dd < dis[j]) {

					dis[j] = dd;
					pre[j] = v;
				}
			}
		}
	}
	/*for (int i = 1; i <= 8; i++) {
		cout << i << " " << dis[i] << endl;
	}*/
}

//输出从pa到pb的最短路径 
void adjMatrix::outputPath(int pa, int pb, string* in, int* pre, int su) {
	if (pa == pb)
		return;
	int temp[sn];
	int co = 1;//计数器 
	temp[co] = pb;//终点 
	co++;
	int te = pre[pb];//pb的前驱 
	while (te != pa) {//将路径上的点存到temp数组中 
		temp[co] = te;
		co++;
		te = pre[te];
	}
	temp[co] = pa;
	int info = theMatrix[temp[co]][temp[co - 1]].ro[search(temp[co], temp[co - 1], su)].Info;
	cout << "线路" << info << "：";

	for (int i = co; i >= 1; i--) {//倒序输出 
		if (i != 1) {
			if (theMatrix[temp[i]][temp[i - 1]].ro[search(temp[i], temp[i - 1], su)].Info != info) {
				//cout<<"测试："<<in[temp[i]]<<" "<<in[temp[i-1]]<<endl;
				cout << "站点" << in[temp[i]] << "。";
				cout << "换乘线路" << theMatrix[temp[i]][temp[i - 1]].ro[search(temp[i], temp[i - 1], su)].Info << "：";
				cout << "站点" << in[temp[i]] << ",";
			}
			else {
				cout << "站点" << in[temp[i]] << ",";
			}
			info = theMatrix[temp[i]][temp[i - 1]].ro[search(temp[i], temp[i - 1], su)].Info;//更新当前线路信息			
		}
		else {//最后一个站点 
			cout << "站点" << in[temp[i]] << "。" << endl;
		}

	}
}

//求da到其他所有点的最短路径长度，加入等待时间 
void adjMatrix::Dijkstra2(double* dis, int* pre, int da, int su, busRoute* bus) {
	int* vis = new int[30];//标记数组
	//memset(&vis, 0, 30);
	for (int i = 1; i <= n; i++) {//初始化为未访问过
		vis[i] = 0;
	}
	for (int i = 1; i <= 26; i++) {
		dis[i] = theMatrix[da][i].ro[search(da, i, su)].data;
		//出发站点，不需要考虑等待时间
		//cout<<"测试："<<this->search(da,i,su)<<" "<<dis[i]<<endl;
		if (dis[i] == noEdge)
			pre[i] = 0;
		else
			pre[i] = da;
	}
	dis[da] = 0;//da到da距离为0 
	/*for(int i=1;i<=8;i++) {
		cout<<i<<" "<<dis[i]<<endl;
	}*/
	cout << endl;
	vis[da] = 1;//标记为访问过 
	int tt = 1;
	for (int i = 1; i <= 26; i++) {
		double temp = noEdge;
		int v = 0;
		for (int j = 1; j <= 26; j++) {//找出距离 点集 最近的点 
			if (vis[j] == 0 && dis[j] < temp) {
				//cout << j << endl;
				v = j;
				temp = dis[j];
			}
		}
		vis[v] = 1;
		int oldInfo;
		if (tt == 1) {
			oldInfo = theMatrix[da][v].ro[search(da, v, su)].Info;//oldInfo初始赋值
		}
		tt = 2;
		for (int j = 1; j <= 26; j++) {
			if (oldInfo == theMatrix[v][j].ro[search2(v, j, su, bus)].Info) {//相同线路，不需加入等待时间
				if (vis[j] == 0 && theMatrix[v][j].ro[search2(v, j, su, bus)].data < noEdge) {//更新 
					double dd = dis[v] + theMatrix[v][j].ro[search2(v, j, su, bus)].data;
					//cout << "sss" << theMatrix[v][j].ro[search2(v, j, su, bus)].data << endl;
					if (dd < dis[j]) {
						dis[j] = dd;
						pre[j] = v;
					}
				}
			}
			else {//不同线路，需要加入等待时间
				if (vis[j] == 0 && theMatrix[v][j].ro[search2(v, j, su, bus)].data + find_(theMatrix[v][j].ro[search2(v, j, su, bus)].Info, su, bus) < noEdge) {//更新 
					double dd = dis[v] + theMatrix[v][j].ro[search2(v, j, su, bus)].data + find_(theMatrix[v][j].ro[search2(v, j, su, bus)].Info, su, bus);
					//cout << "sss" << theMatrix[v][j].ro[search2(v, j, su, bus)].data << endl;
					if (dd < dis[j]) {
						dis[j] = dd;
						pre[j] = v;
					}
					oldInfo = theMatrix[v][j].ro[search2(v, j, su, bus)].Info;//oldInfo更新
				}
			}
		}
	}
	/*for (int i = 1; i <= 8; i++) {
		cout << i << " " << dis[i] << endl;
	}*/
}

//找出站点i到站点j的所有公交线路中的最优解 ，su表示两站点之间的线路条数 
int adjMatrix::search(int i, int j, int su) {
	double qq = theMatrix[i][j].ro[1].data;
	int uu = 1;
	for (int k = 2; k <= su; k++) {
		if (theMatrix[i][j].ro[k].data < qq) {
			qq = theMatrix[i][j].ro[k].data;
			uu = k;
		}
	}
	//cout<<"测试："<<uu<<endl;
	return uu;
}

//查找线路编号对应的等待时间
double adjMatrix::find_(int Information, int su, busRoute* bus) {
	if (Information == 0)
		return 0;
	for (int i = 1; i <= su; i++) {
		if (bus[i].getNum() == Information)
			return bus[i].getTime_();
	}
}

//找出站点i到站点j的所有公交线路中的最优解（加上等待时间） ，su表示两站点之间的线路条数
int adjMatrix::search2(int i, int j, int su, busRoute* bus) {
	double qq = theMatrix[i][j].ro[1].data + find_(theMatrix[i][j].ro[1].Info, su, bus);
	int uu = 1;
	for (int k = 2; k <= su; k++) {
		if (theMatrix[i][j].ro[k].data + find_(theMatrix[i][j].ro[k].Info, su, bus) < qq) {
			qq = theMatrix[i][j].ro[k].data + find_(theMatrix[i][j].ro[k].Info, su, bus);
			//cout << "ttt " << find_(theMatrix[i][j].ro[k].Info, su, bus) << endl;
			uu = k;
		}
	}

	//cout<<"测试："<<uu<<endl;
	return uu;
}
#endif
#pragma once
