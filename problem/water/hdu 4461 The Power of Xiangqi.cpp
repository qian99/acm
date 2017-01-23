#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
bool flag1,flag2;
int getpoints(char c)
{
    int res=0;
    switch(c)
    {
        case 'A':res=16;break;
        case 'B':res=7; break;
        case 'C':res=8; break;
        case 'D':res=1; break;
        case 'E':res=1; break;
        case 'F':res=2; break;
        case 'G':res=3; break;
    }
    if(res==7) flag1=true;
    if(res==8) flag2=true;
    return res;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n;
    char str[5];
    scanf("%d",&t);
    while(t--)
    {
        int red=0,black=0;
        scanf("%d",&n);
        flag1=flag2=false;
        for(int i=1;i<=n;++i)
        {
            scanf("%s",str);
            red+=getpoints(str[0]);
        }
        if(!flag1||!flag2) red--;
        if(red==0) red++;
        scanf("%d",&n);
        flag1=flag2=false;
        for(int i=1;i<=n;++i)
        {
            scanf("%s",str);
            black+=getpoints(str[0]);
        }
        if(!flag1||!flag2) black--;
        if(black==0) black++;
        if(red==black) printf("tie\n");
        else if(red>black) printf("red\n");
        else printf("black\n");
    }
    return 0;
}
