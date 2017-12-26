//计算任意两个日期之间相差的天数
#include <iostream>
#include <vector>
#include <ctime>
#include <wchar.h>
#include <string>
#include <stdio.h>
#include <memory.h>
using namespace std;

double dayCount(string date1, string date2){
    tm tm1, tm2;
    memset(&tm1, 0, sizeof(tm1));
    memset(&tm2, 0, sizeof(tm2));
    strptime(date1.data(),"%Y-%m-%d",&tm1);
    strptime(date2.data(),"%Y-%m-%d",&tm2);
   
    return difftime(mktime(&tm2), mktime(&tm1)) / 86400;
}

int main(){
    string date1 = "2017-02-28";
    string date2 = "2017-03-01";

    cout << dayCount(date1, date2) << endl;

    return 0;
}