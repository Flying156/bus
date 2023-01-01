
#include <iostream>
#include "busChain.h"
#include "busRoute.h"
#include "Martix.h"
#include <string.h>
#include <string>
#include <iomanip>
#include <cmath> 
#define sn 30//站点总数 
#define noEdge 9999
using namespace std;

//函数声明 
void Welcome();
void Input();
void Menu();
int choose();
void Function();
void findMinCost();
void findMinTime();
void findMinTran();
void Dijkstra(int da);
int getIndex(string bs);
void outputPath(int pa, int pb);
void Dijkstra2(int da);
int find_(int Infomation);

//全局变量 
int option;//进行功能选择
char flag = 'y';//每个功能完成后判断是否退出
busRoute *bus = new busRoute[10];//公交车线路数组 
int BUS_SUM;//公交线路数
string in[sn] = { " ","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"," "," "," " };
//已有对应关系，将站点名和站点标号对应 
int vis[sn];//判断是否访问过 
int	pre[sn];//前驱 
double dis[sn];//到源点的距离
adjMatrix matrix(30);//邻接矩阵


int main() {
	Welcome();
	Input();
	Menu();
	return 0;
}

//欢迎界面 
void Welcome() {
	cout << "\n\n";
	cout << "\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\t\n";
	cout << "\t*\t\t\t\t\t\t\t\t*\n";
	cout << "\t*\t\t欢迎使用公交线路查询系统\t\t\t*\n";
	cout << "\t*\t\t\t\t\t\t\t\t*\n";
	cout << "\t*\t\t\t\t\t\t\t\t*\n";
	cout << "\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\t\n";
	cout << endl << endl;
	cout << "=------------------------------------------------------------------------------=\n";
}

//输入线路信息 
void Input() {
	cout << "请输入线路总条数：";
	cin >> BUS_SUM;
	int n, nn;
	for (int i = 1; i <= BUS_SUM; i++) {
		cout << "请输入第" << i << "条线路的编号：";
		cin >> nn;
		cout << "请输入第" << i << "条线路的站点个数：";
		cin >> n;
		bus[i].initi1(nn, n);
		cout << "请输入第" << i << "条线路的票价(元)、发车间隔(分钟)、速度(每分钟)，以空格分隔：";
		int tt;
		double xp, yp;
		cin >> xp >> yp >> tt;
		bus[i].initi2(xp, yp, tt);//设置票价、发车间隔、速度
	}
	
}


//菜单 
void Menu() {
	for(int i = 1; i <= BUS_SUM; i++)
		bus[i].link.get_distance();
	while (flag == 'y') {
		cout << "\n\n";
		cout << "\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\t\n";
		cout << "\t*\t\t\t\t\t\t\t\t*\n";
		cout << "\t*\t\t欢迎使用公交线路优化查询系统\t\t\t*\n";
		cout << "\t* _____________________________________________________________ *\t\n";
		cout << "\t* ------------------------------------------------------------- *\t\n";
		cout << "\t*\t\t\t\t\t\t\t\t*\n";
		cout << "\t*\t\t\t\t\t\t\t\t*\n";
		cout << "\t* \t使用帮助：请查看下列菜单输入项目对应标号进入查询。\t*\n";
		cout << "\t* ------------------------------------------------------------- *\t\n";
		cout << "\t*\t\t\t\t\t\t\t\t*\n";
		cout << "\t*\t\t1-查询两站点最省钱方案；\t\t\t*\t\n";
		cout << "\t*\t\t\t\t\t\t\t\t*\n";
		cout << "\t*\t\t2-查询两站点最省时方案；\t*\t\n";
		cout << "\t*\t\t\t\t\t\t\t\t*\n";
		cout << "\t*\t\t3-查询两站点最少换乘方案；\t*\t\n";
		cout << "\t*\t\t\t\t\t\t\t\t*\n";
		cout << "\t*\t\t4-退出。\t\t\t\t\t*\t\n";
		cout << "\t*\t\t\t\t\t\t\t\t*\n";
		cout << "\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\t\n";
		cout << endl << endl;
		Function();//选择功能 
	} 
}

//功能 
void Function() {
	cout << "=------------------------------------------------------------------------------=\n";
	cout << "\t请输入你的选择：";
	cin >> option;
	cout << "=------------------------------------------------------------------------------=\n";
	
	if (option == 1)
		findMinCost();//查找最少花费 
	else if (option == 2 )
		findMinTime();//查找最少时间
	else if(option == 3)
		findMinTran();
	else if(option==4) {
		cout<<"\t已退出“公交路径查询系统”！"<<endl;
		flag='n';
		return;//返回，结束
	}
	else {
		cout << "\t您输入的指令有误！\n\n\n";
		cout << "___________________________________________________________________________________\n";
		cout << "-----------------------------------------------------------------------------------\n\n";
	}
	
}

//查找最少花费 
void findMinCost() {
	cout << "正在使用Function1-查询两站点最省钱方案；" << endl;
	cout << "=------------------------------------------------------------------------------=\n";
	matrix.ini();
	routeInfo rI;
	//建立票价邻接矩阵 
	for (int i = 1; i <= BUS_SUM; i++) {
		rI.Info = bus[i].getNum();
		rI.data = bus[i].getPrice();
		busNode *p = bus[i].getLink().getFirst();
		for (p; p != NULL; p = p->next) {
			busNode *pp = p->next;
			int ta = getIndex(p->sta_name);
			for (pp; pp != NULL; pp = pp->next) {
				int tb = getIndex(pp->sta_name);
				matrix.insert(ta, tb, i, rI);
				matrix.insert(tb, ta, i, rI);
				//取最短的边 
			}
		}
	}
	
	string sa, sb;
	cout << "请输入出发站点和目的站点（以空格分隔）：";
	cin >> sa >> sb;
	matrix.Dijkstra(dis, pre, getIndex(sa), BUS_SUM);
	if (dis[getIndex(sb)] == noEdge) {
		cout << "无法利用目前已有线路从" << sa << "到达" << sb << "！" << endl;
		cout << "=------------------------------------------------------------------------------=\n";
	}
	else {
		matrix.outputPath(getIndex(sa), getIndex(sb), in, pre, BUS_SUM);
		cout << "共花费" << setiosflags(ios::fixed) << setprecision(0) << dis[getIndex(sb)] << "元。" << endl << endl;
	}
	cout << "=------------------------------------------------------------------------------=\n";
	
	return;
}


void findMinTran(){
	cout << "正在使用Function1-查询两站点最少换乘方案；" << endl;
	cout << "=------------------------------------------------------------------------------=\n";
	matrix.ini();
	routeInfo rI;
	//建立票价邻接矩阵 
	for (int i = 1; i <= BUS_SUM; i++) {
		rI.Info = bus[i].getNum();
		rI.data = bus[i].getPrice();
		busNode *p = bus[i].getLink().getFirst();
		for (p; p != NULL; p = p->next) {
			busNode *pp = p->next;
			int ta = getIndex(p->sta_name);
			for (pp; pp != NULL; pp = pp->next) {
				int tb = getIndex(pp->sta_name);
				matrix.insert(ta, tb, i, rI);
				matrix.insert(tb, ta, i, rI);
				//取最短的边 
			}
		}
	}
	
	string sa, sb;
	cout << "请输入出发站点和目的站点（以空格分隔）：";
	cin >> sa >> sb;
	matrix.Dijkstra(dis, pre, getIndex(sa), BUS_SUM);
	if (dis[getIndex(sb)] == noEdge) {
		cout << "无法利用目前已有线路从" << sa << "到达" << sb << "！" << endl;
		cout << "=------------------------------------------------------------------------------=\n";
	}
	else {
		matrix.outputPath(getIndex(sa), getIndex(sb), in, pre, BUS_SUM);
		cout << "共换乘" << setiosflags(ios::fixed) << setprecision(0) << dis[getIndex(sb)] / 2 - 1 << "次。" << endl << endl;
	}
	cout << "=------------------------------------------------------------------------------=\n";
	
	return;
}

//查找最少时间
void findMinTime() {
	cout << "正在使用Function2-查询两站点最省时方案；" << endl;
	cout << "=------------------------------------------------------------------------------=\n";
	matrix.ini();
	routeInfo rI;
	//建立耗费时间邻接矩阵 
	for (int i = 1; i<=BUS_SUM; i++) {
		rI.Info = bus[i].getNum();
		busNode *p = bus[i].getLink().getFirst();
		for (p; p != NULL; p = p->next) {
			busNode *pp = p->next;
			int ta = getIndex(p->sta_name);
			if (pp != NULL) {
				double ddis = p->dx;
				rI.data = ddis / bus[i].getSpeed();//时间 
				//cout<<rI.data<<endl;
				int tb = getIndex(pp->sta_name);
				matrix.insert(ta, tb, i, rI);
				matrix.insert(tb, ta, i, rI);
			}
		}
	}
	
	string sa, sb;
	cout << "请输入出发站点和目的站点（以空格分隔）：";
	cin >> sa >> sb;
	
	matrix.Dijkstra(dis, pre,getIndex(sa), BUS_SUM);
	if (dis[getIndex(sb)] == noEdge) {
		cout << "无法利用目前已有线路从" << sa << "到达" << sb << "！" << endl;
		cout << "=------------------------------------------------------------------------------=\n";
	}
	else {
		matrix.outputPath(getIndex(sa), getIndex(sb), in, pre, BUS_SUM);
		//outputPath(getIndex(sa),getIndex(sb));
		cout << "共花费" << setiosflags(ios::fixed) << setprecision(2) << dis[getIndex(sb)] << "分钟时间。" << endl << endl;
	}
	cout << "=------------------------------------------------------------------------------=\n";
	return;
}



//得到各站点索引 
int getIndex(string bs) {
	for (int i = 1; i <= 26; i++) {
		if (in[i] == bs)
			return i;
	}
	return -1;
}

