#include <iostream>
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
const int maxn=1000+10;
ll C[4][maxn][maxn];
inline int lowbit(int x)
{
    return x&(-x);
}
int getw(int x,int y)
{
    int res=0;
    if(x&1) res+=1;
    if(y&1) res+=2;
    return res;
}
void update(int x,int y,ll v)
{
    int wh=getw(x,y);
    for(int i=x;i<maxn;i+=lowbit(i))
        for(int j=y;j<maxn;j+=lowbit(j))
            C[wh][i][j]^=v;
}
ll query(int x,int y)
{
    int wh=getw(x,y);
    ll res=0;
    for(int i=x;i>0;i-=lowbit(i))
        for(int j=y;j>0;j-=lowbit(j))
            res^=C[wh][i][j];
    return res;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    memset(C,0,sizeof(C));
    scanf("%d%d",&n,&m);
    int x0,y0,x1,y1,type;
    ll v;
    while(m--)
    {
        scanf("%d",&type);
        scanf("%d%d%d%d",&x0,&y0,&x1,&y1);
        if(type==1)
        {
            ll res=query(x1,y1);
            res^=query(x1,y0-1);
            res^=query(x0-1,y1);
            res^=query(x0-1,y0-1);
            printf("%I64d\n",res);
        }
        else
        {
            scanf("%I64d",&v);
            update(x0,y0,v);
            update(x0,y1+1,v);
            update(x1+1,y0,v);
            update(x1+1,y1+1,v);
        }
    }
    return 0;
}
