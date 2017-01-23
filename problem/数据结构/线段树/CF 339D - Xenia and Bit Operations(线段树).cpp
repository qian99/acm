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
const int maxn=(1<<18)+10;
int val[maxn],type[maxn];
void PushUp(int rt)
{
    type[rt]=type[rt<<1]^1;
    if(type[rt]) val[rt]=val[rt<<1]|val[rt<<1|1];
    else val[rt]=val[rt<<1]^val[rt<<1|1];
}
void build(int l,int r,int rt)
{
    if(l==r)
    {
        scanf("%d",&val[rt]);
        type[rt]=0;
        return;
    }
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
    PushUp(rt);
}
void Update(int p,int l,int r,int rt,int v)
{
    if(l==r)
    {
        val[rt]=v;
        return;
    }
    int m=(l+r)>>1;
    if(m>=p) Update(p,l,m,rt<<1,v);
    else Update(p,m+1,r,rt<<1|1,v);
    PushUp(rt);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m,N;
    scanf("%d%d",&n,&m);
    N=1<<n;
    build(1,N,1);
    int p,v;
    while(m--)
    {
        scanf("%d%d",&p,&v);
        Update(p,1,N,1,v);
        printf("%d\n",val[1]);
    }
    return 0;
}
