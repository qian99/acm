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
const int maxn=10000+10;
const int maxm=50000+10;
int u[maxm],v[maxm],w[maxm],s[maxm],ans;
int parents[maxn],sum[maxn],res[maxn];
struct Node
{
    int l,num;
    bool operator < (const Node &a) const
    {
        return l<a.l;
    }
};
Node node[maxn];
bool cmp(int a,int b)
{
    return w[a]<w[b];
}
int Find(int x)
{
    return x!=parents[x]?parents[x]=Find(parents[x]):x;
}
void Uion(int x,int y)
{
    x=Find(x);
    y=Find(y);
    if(x!=y)
    {
        parents[y]=x;
        ans+=sum[x]*sum[y];
        sum[x]+=sum[y];
        sum[y]=0;
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m,q;
    while(~scanf("%d%d%d",&n,&m,&q))
    {
        for(int i=1;i<=n;++i)
        {
            parents[i]=i;
            sum[i]=1;
        }
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&u[i],&v[i],&w[i]);
            s[i]=i;
        }
        sort(s,s+m,cmp);
        for(int i=0;i<q;++i)
        {
            scanf("%d",&node[i].l);
            node[i].num=i;
        }
        sort(node,node+q);
        int p=0,z=0;
        ans=0;
        while(p<m&&z<q)
        {
            while(w[s[p]]<=node[z].l&&p<m) {Uion(u[s[p]],v[s[p]]);p++;}
            res[node[z].num]=ans;
            z++;
        }
        for(;z<q;++z) res[node[z].num]=ans;
        for(int i=0;i<q;++i)
          printf("%d\n",res[i]);
    }
    return 0;
}
