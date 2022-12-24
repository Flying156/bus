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

//��վ��֮�����·��Ϣ
struct routeInfo {
	int Info;//��·��� 
	double data;//���� 
};

//��վ��֮�����·��Ϣ�����ж�����·
struct ver {
	routeInfo ro[sn];//ÿ����·��Ϣ 
};

class adjMatrix {
public:
	adjMatrix(int theCapacity);//���캯��
	~adjMatrix();//��������

	void insert(int i, int j, int nth, routeInfo rt);//����Ԫ��
	void erase(int i, int j, int nth);//ɾ��Ԫ�� 
	double getElement(int i, int j, int nth);//���� 
	int getM() const {//�õ��ܱ���
		return m;
	}
	void ini();//��ʼ��Ϊ�ޱ�
	int search(int i, int j, int su);//����վ��i��վ��j��������·�е����Ž�
	int search2(int i, int j, int su, busRoute* bus);//����վ��i��վ��j��������·�е����Ž⣨�ж��Ƿ����ȴ�ʱ�䣩
	void Dijkstra(double* dis, int* pre, int da, int su);//��da������������·��
	void outputPath(int pa, int pb, string* in, int* pre, int su);//���pa��pb�������·
	void Dijkstra2(double* dis, int* pre, int da, int su, busRoute* bus); //��da������������·���������м�վ��ĵȴ�ʱ��
	double find_(int Infomation, int su, busRoute* bus);//������·��Ŷ�Ӧ�ĵȴ�ʱ��

private:
	ver** theMatrix;//�ڽӾ���
	int n;//���� 
	int m;//���� 

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
	m = 0;//����
	n = 0;//����
}

void adjMatrix::insert(int i, int j, int nth, routeInfo rt) {//��i-j���ĵ�nth����·��Ϣ�в���rt
	if (theMatrix[i][j].ro[nth].data == noEdge) {
		theMatrix[i][j].ro[nth] = rt;
		m++;//���� 
	}
	else {//���бߣ�������Ϣ
		theMatrix[i][j].ro[nth] = rt;
	}

}

void adjMatrix::erase(int i, int j, int nth) {//ɾ��i-j���ĵ�nth����·�ı�
	if (theMatrix[i][j].ro[nth].data == noEdge) {
		cout << "Error!" << endl;
	}
	else {
		theMatrix[i][j].ro[nth].data = noEdge;
		m--;//����
	}
}

double adjMatrix::getElement(int i, int j, int nth) {//�õ�i-j���ĵ�nth����·�ı�ֵ
	return theMatrix[i][j].ro[nth].data;
}


void adjMatrix::ini() {//��ʼ����Ϊ�ޱߣ���·��ž�Ϊ0 
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			for (int k = 1; k <= sn; k++) {
				theMatrix[i][j].ro[k].data = noEdge;
				theMatrix[i][j].ro[k].Info = 0;
			}

		}
	}
}

//��da���������е�����·������
void adjMatrix::Dijkstra(double* dis, int* pre, int da, int su) {
	int* vis = new int[30];//�������
	//memset(&vis, 0, 30);
	for (int i = 1; i <= n; i++) {//��ʼ��Ϊδ���ʹ�
		vis[i] = 0;
	}
	for (int i = 1; i <= 26; i++) {
		dis[i] = theMatrix[da][i].ro[search(da, i, su)].data;
		//cout<<"���ԣ�"<<this->search(da,i,su)<<" "<<dis[i]<<endl;
		if (dis[i] == noEdge)
			pre[i] = 0;
		else
			pre[i] = da;
	}
	dis[da] = 0;//da��da����Ϊ0 
	/*for(int i=1;i<=8;i++) {
		cout<<i<<" "<<dis[i]<<endl;
	}
	cout<<endl;*/
	vis[da] = 1;//���Ϊ���ʹ� 

	for (int i = 1; i <= 25; i++) {
		double temp = noEdge;
		int v = 0;
		for (int j = 1; j <= 26; j++) {//�ҳ����� �㼯 ����ĵ� 
			if (vis[j] == 0 && dis[j] < temp) {
				//cout << j << endl;
				v = j;
				temp = dis[j];
			}
		}
		vis[v] = 1;
		for (int j = 1; j <= 26; j++) {
			if (vis[j] == 0 && theMatrix[v][j].ro[search(v, j, su)].data < noEdge) {//���� 
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

//�����pa��pb�����·�� 
void adjMatrix::outputPath(int pa, int pb, string* in, int* pre, int su) {
	if (pa == pb)
		return;
	int temp[sn];
	int co = 1;//������ 
	temp[co] = pb;//�յ� 
	co++;
	int te = pre[pb];//pb��ǰ�� 
	while (te != pa) {//��·���ϵĵ�浽temp������ 
		temp[co] = te;
		co++;
		te = pre[te];
	}
	temp[co] = pa;
	int info = theMatrix[temp[co]][temp[co - 1]].ro[search(temp[co], temp[co - 1], su)].Info;
	cout << "��·" << info << "��";

	for (int i = co; i >= 1; i--) {//������� 
		if (i != 1) {
			if (theMatrix[temp[i]][temp[i - 1]].ro[search(temp[i], temp[i - 1], su)].Info != info) {
				//cout<<"���ԣ�"<<in[temp[i]]<<" "<<in[temp[i-1]]<<endl;
				cout << "վ��" << in[temp[i]] << "��";
				cout << "������·" << theMatrix[temp[i]][temp[i - 1]].ro[search(temp[i], temp[i - 1], su)].Info << "��";
				cout << "վ��" << in[temp[i]] << ",";
			}
			else {
				cout << "վ��" << in[temp[i]] << ",";
			}
			info = theMatrix[temp[i]][temp[i - 1]].ro[search(temp[i], temp[i - 1], su)].Info;//���µ�ǰ��·��Ϣ			
		}
		else {//���һ��վ�� 
			cout << "վ��" << in[temp[i]] << "��" << endl;
		}

	}
}

//��da���������е�����·�����ȣ�����ȴ�ʱ�� 
void adjMatrix::Dijkstra2(double* dis, int* pre, int da, int su, busRoute* bus) {
	int* vis = new int[30];//�������
	//memset(&vis, 0, 30);
	for (int i = 1; i <= n; i++) {//��ʼ��Ϊδ���ʹ�
		vis[i] = 0;
	}
	for (int i = 1; i <= 26; i++) {
		dis[i] = theMatrix[da][i].ro[search(da, i, su)].data;
		//����վ�㣬����Ҫ���ǵȴ�ʱ��
		//cout<<"���ԣ�"<<this->search(da,i,su)<<" "<<dis[i]<<endl;
		if (dis[i] == noEdge)
			pre[i] = 0;
		else
			pre[i] = da;
	}
	dis[da] = 0;//da��da����Ϊ0 
	/*for(int i=1;i<=8;i++) {
		cout<<i<<" "<<dis[i]<<endl;
	}*/
	cout << endl;
	vis[da] = 1;//���Ϊ���ʹ� 
	int tt = 1;
	for (int i = 1; i <= 26; i++) {
		double temp = noEdge;
		int v = 0;
		for (int j = 1; j <= 26; j++) {//�ҳ����� �㼯 ����ĵ� 
			if (vis[j] == 0 && dis[j] < temp) {
				//cout << j << endl;
				v = j;
				temp = dis[j];
			}
		}
		vis[v] = 1;
		int oldInfo;
		if (tt == 1) {
			oldInfo = theMatrix[da][v].ro[search(da, v, su)].Info;//oldInfo��ʼ��ֵ
		}
		tt = 2;
		for (int j = 1; j <= 26; j++) {
			if (oldInfo == theMatrix[v][j].ro[search2(v, j, su, bus)].Info) {//��ͬ��·���������ȴ�ʱ��
				if (vis[j] == 0 && theMatrix[v][j].ro[search2(v, j, su, bus)].data < noEdge) {//���� 
					double dd = dis[v] + theMatrix[v][j].ro[search2(v, j, su, bus)].data;
					//cout << "sss" << theMatrix[v][j].ro[search2(v, j, su, bus)].data << endl;
					if (dd < dis[j]) {
						dis[j] = dd;
						pre[j] = v;
					}
				}
			}
			else {//��ͬ��·����Ҫ����ȴ�ʱ��
				if (vis[j] == 0 && theMatrix[v][j].ro[search2(v, j, su, bus)].data + find_(theMatrix[v][j].ro[search2(v, j, su, bus)].Info, su, bus) < noEdge) {//���� 
					double dd = dis[v] + theMatrix[v][j].ro[search2(v, j, su, bus)].data + find_(theMatrix[v][j].ro[search2(v, j, su, bus)].Info, su, bus);
					//cout << "sss" << theMatrix[v][j].ro[search2(v, j, su, bus)].data << endl;
					if (dd < dis[j]) {
						dis[j] = dd;
						pre[j] = v;
					}
					oldInfo = theMatrix[v][j].ro[search2(v, j, su, bus)].Info;//oldInfo����
				}
			}
		}
	}
	/*for (int i = 1; i <= 8; i++) {
		cout << i << " " << dis[i] << endl;
	}*/
}

//�ҳ�վ��i��վ��j�����й�����·�е����Ž� ��su��ʾ��վ��֮�����·���� 
int adjMatrix::search(int i, int j, int su) {
	double qq = theMatrix[i][j].ro[1].data;
	int uu = 1;
	for (int k = 2; k <= su; k++) {
		if (theMatrix[i][j].ro[k].data < qq) {
			qq = theMatrix[i][j].ro[k].data;
			uu = k;
		}
	}
	//cout<<"���ԣ�"<<uu<<endl;
	return uu;
}

//������·��Ŷ�Ӧ�ĵȴ�ʱ��
double adjMatrix::find_(int Information, int su, busRoute* bus) {
	if (Information == 0)
		return 0;
	for (int i = 1; i <= su; i++) {
		if (bus[i].getNum() == Information)
			return bus[i].getTime_();
	}
}

//�ҳ�վ��i��վ��j�����й�����·�е����Ž⣨���ϵȴ�ʱ�䣩 ��su��ʾ��վ��֮�����·����
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

	//cout<<"���ԣ�"<<uu<<endl;
	return uu;
}
#endif
#pragma once
