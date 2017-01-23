#include <iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
const int ddl[2][13]={{0,31,29,31,30,31,30,31,31,30,31,30,31},{0,31,28,31,30,31,30,31,31,30,31,30,31}};
bool isleapyear(int year)
{
    return (year%4==0&&year%100!=0)||(year%400==0);
}
int cc(int year,int mon1,int day1,int mon2,int day2)
{
    if(mon1==mon2) return day2-day1;
    int u=(isleapyear(year))?0:1;
    int sum=ddl[u][mon1]-day1;
    mon1++;
    while(mon1<mon2)
    {
        sum+=ddl[u][mon1];
        mon1++;
    }
    sum+=day2;
    return sum;
}
int yy(int year1,int mon1,int day1,int year2,int mon2,int day2)
{
    if(year1==year2) return cc(year1,mon1,day1,mon2,day2);
    int sum=cc(year1,mon1,day1,12,31);
    year1++;
    while(year1<year2)
    {
        if(isleapyear(year1))
          sum+=366;
        else
          sum+=365;
        year1++;
    }
    sum+=cc(year2,1,1,mon2,day2);
    return sum+1;
}
void sortdate(int &year1,int &mon1,int &day1,int &year2,int &mon2,int &day2)
{
    bool flag=false;
    if(year1>year2)
        flag=true;
    else if(year1<year2)
        return ;
    if(!flag&&mon1>mon2)
        flag=true;
    else if(!flag&&mon1<mon2)
        return ;
    if(!flag&&day1>day2)
        flag=true;
    else if(!flag&&day1<day2)
        return ;
    if(flag)
    {
        swap(year1,year2);
        swap(mon1,mon2);
        swap(day1,day2);
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int year1,mon1,day1,year2,mon2,day2;
    scanf("%d:%d:%d",&year1,&mon1,&day1);
    scanf("%d:%d:%d",&year2,&mon2,&day2);
    sortdate(year1,mon1,day1,year2,mon2,day2);
    printf("%d\n",yy(year1,mon1,day1,year2,mon2,day2));
    return 0;
}
