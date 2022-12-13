#include "busRoute.h"
#include <iostream>

using namespace std;
timeNode b, c;
int main()
{
    b.hour = 7;
    b.hour = 35;
    b.sec = 40;
    c.hour = 17;
    c.hour = 35;
    c.sec = 40;
    busRoute* a = new busRoute();
    a->init1(2, "k7");
    a->init2(b, c, 80.0);
}