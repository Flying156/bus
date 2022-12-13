#include <graphics.h>
#include <iostream>

using namespace std;
struct Station { //公交所经过的站点
    int x, y;
};
struct Time { //时间
    int hour, minute, sec;
};
struct Bus { //公交线路
    int price, speed;
    string name;
    Station station[100];
    Time BeignTime, EndTime;
};
void input() {//输入信息

}
int main() {

}