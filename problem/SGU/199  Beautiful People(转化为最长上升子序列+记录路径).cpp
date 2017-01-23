#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=100000+10;
struct Node
{
    int s,b,id;
    bool operator <(const Node &a) const
    {
        return (s==a.s&&b>a.b)||(s<a.s);
    }
}node[maxn];
int S[maxn],num[maxn],pa[maxn];
int f(int l,int r,int v)
{
    int m;
    while(l<r)
    {
        m=(l+r)>>1;
        if(S[m]<v)
          l=m+1;
        else
          r=m;
    }
    return l;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d",&node[i].s,&node[i].b);
        node[i].id=i;
    }
    memset(num,0,sizeof(num));
    memset(pa,0,sizeof(pa));
    sort(node+1,node+n+1);
    S[1]=node[1].b;num[1]=node[1].id;
    int top=1;
    for(int i=2;i<=n;++i)
    {
        if(node[i].b>S[top])
        {
            S[++top]=node[i].b;
            num[top]=node[i].id;
            pa[node[i].id]=num[top-1];
        }
        else
        {
            int pos=f(1,top,node[i].b);
            S[pos]=node[i].b;
            num[pos]=node[i].id;
            pa[node[i].id]=num[pos-1];
        }
    }
    printf("%d\n",top);
    int u=num[top];
    bool first=true;
    while(u)
    {
        if(!first) printf(" ");
        first=false;
        printf("%d",u);
        u=pa[u];
    }
    printf("\n");
    return 0;
}
