#include <iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<stack>
#include<queue>
#include<set>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define pi acos(-1.0)
using namespace std;
const int maxn=100000+10;
int dp[11][83][83][83];
int num[11];
int f(int pos,int x,int y,int mod,bool limit)
{
    if(pos==-1) return x==0&&y==0;
    if(!limit&&dp[pos][x][y][mod]!=-1) return dp[pos][x][y][mod];
    int res=0;
    int last=limit?num[pos]:9;
    for(int i=0;i<=last;++i)
    {
        if(y<i) break;
        res+=f(pos-1,(x*10+i)%mod,y-i,mod,limit&&i==last);
    }
    if(!limit) dp[pos][x][y][mod]=res;
    return res;
}
int cal(int x)
{
    int len=0;
    while(x)
    {
        num[len++]=x%10;
        x/=10;
    }
    int res=0;
    for(int i=1;i<=82;++i)
    {
        res+=f(len-1,0,i,i,true);
    }
    return res;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    memset(dp,0xff,sizeof(dp));
    int t,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        int A,B;
        scanf("%d%d",&A,&B);
        int res=cal(B)-cal(A-1);
        printf("Case %d: %d\n",++tcase,res);
    }
    return 0;
}