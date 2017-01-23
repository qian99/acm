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
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
int cal(int d1,int d2,int a,int b,bool A,bool B)
{
    if(d1 % a != 0) return inf;
    if(d2 % b != 0) return inf;
    d1 /= a;
    d2 /= b;
    if(d1 == 0 && d2 == 0) return 0;
    if(d1 == 0 && !A) return inf;
    if(d2 == 0 && !B) return inf;
    if(d1 > d2) swap(d1,d2);
    if((d2-d1)%2 != 0) return inf;
    return d2;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n,m,x,y,a,b;
    scanf("%d%d%d%d%d%d",&n,&m,&x,&y,&a,&b);
    int ans = inf;
    ans = min(ans,cal(x-1,y-1,a,b,x-a>=1||x+a<=n,y-b>=1||y+b<=m));
    ans = min(ans,cal(n-x,m-y,a,b,x-a>=1||x+a<=n,y-b>=1||y+b<=m));
    ans = min(ans,cal(x-1,m-y,a,b,x-a>=1||x+a<=n,y-b>=1||y+b<=m));
    ans = min(ans,cal(n-x,y-1,a,b,x-a>=1||x+a<=n,y-b>=1||y+b<=m));
    if(ans == inf) puts("Poor Inna and pony!");
    else printf("%d\n",ans);
    return 0;
}
