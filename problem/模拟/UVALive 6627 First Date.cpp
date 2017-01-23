#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<set>
#include<cmath>
#include<vector>
#include<bitset>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int mday[13] = {0,31,29,31,30,31,30,31,31,30,31,30,31};
const int xday[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
const int maxn = 10000 + 10;
inline bool oldleapyear(int year)
{
    return year % 4 == 0;
}
inline bool leapyear(int year)
{
    return (year%4 == 0 && year % 100 != 0)||(year%400 == 0);
}
int sum[maxn];
void Init()
{
    memset(sum,0,sizeof(sum));
    sum[1581] = 11;
    for(int i = 1582;i < maxn;++i)
    {
        if(oldleapyear(i) && !leapyear(i))
            sum[i]++;
        sum[i] += sum[i-1];
    }
}
int caldays(int year,int month,int days)
{
    int tot = 0;
    tot = sum[year - 1];
    if(oldleapyear(year) && !leapyear(year))
    {
        if(month >= 3 || (month == 2 && days == 29))
            tot++;
    }
    return tot;
}
inline void ajust(int & year,int & month,int & day)
{
    if(leapyear(year))
    {
        if(day > mday[month])
        {
            day = 1;
            month++;
            if(month > 12)
            {
                month = 1;
                year++;
            }
        }
    }
    else
    {
        if(day > xday[month])
        {
            day = 1;
            month++;
            if(month > 12)
            {
                month = 1;
                year++;
            }
        }
    }
}
void convert(int & year,int & month,int & day,int x)
{
    if(x == 0) return ;
    day++;
    ajust(year,month,day);
    convert(year,month,day,x-1);
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    Init();
    int year,month,day;
    while(~scanf("%d-%d-%d",&year,&month,&day))
    {
        int sum = caldays(year,month,day);
        convert(year,month,day,sum);
        printf("%04d-%02d-%02d\n",year,month,day);
    }
    return 0;
}

