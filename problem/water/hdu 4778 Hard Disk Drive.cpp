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
int converts(char *a)
{
    if(a[0]=='B') return 0;
    if(a[0]=='K'&&a[1]=='B') return 1;
    if(a[0]=='M'&&a[1]=='B') return 2;
    if(a[0]=='G'&&a[1]=='B') return 3;
    if(a[0]=='T'&&a[1]=='B') return 4;
    if(a[0]=='P'&&a[1]=='B') return 5;
    if(a[0]=='E'&&a[1]=='B') return 6;
    if(a[0]=='Z'&&a[1]=='B') return 7;
    return 8;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        int k;
        tcase++;
        char str[5];
        scanf("%d[%s]",&k,str);
        int x=converts(str);
        double res=1,tmp;
        tmp=1000.0/1024;
        for(int i=0;i<x;++i)
          res*=tmp;
        res=1.0-res;
        res*=100;
        printf("Case #%d: %.2lf%%\n",tcase,res);
    }
    return 0;
}
