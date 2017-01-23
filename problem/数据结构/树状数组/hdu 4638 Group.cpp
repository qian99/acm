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
const int maxn=100000+10;
struct Query
{
    int L,R,id;
    bool operator < (const Query & a) const
    {
        return R>a.R;
    }
}query[maxn];
int n,m;
int c[maxn],ans[maxn],num[maxn],pos[maxn];
bool vis[maxn];
int lowbit(int x)
{
    return x&-x;
}
void add(int x,int v)
{
    while(x<=n)
    {
        c[x]+=v;
        x+=lowbit(x);
    }
}
int sum(int x)
{
    int v=0;
    while(x>0)
    {
        v+=c[x];
        x-=lowbit(x);
    }
    return v;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&num[i]);
            pos[num[i]]=i;
        }
        for(int i=0;i<m;++i)
        {
            scanf("%d%d",&query[i].L,&query[i].R);
            query[i].id=i;
        }
        memset(c,0,sizeof(c));
        memset(vis,0,sizeof(vis));
        for(int i=n;i>0;--i)
        {
            vis[num[i]]=true;
            if(vis[num[i]-1]^vis[num[i]+1]) continue;
            if(vis[num[i]-1]&&vis[num[i]+1]) add(i,-1);
            else
              add(i,1);
        }
        memset(vis,0,sizeof(vis));
        sort(query,query+m);
        int j=n;
        for(int i=0;i<m;++i)
        {
            while(j>query[i].R)
            {
                vis[num[j]]=true;
                if(num[j]>1&&!vis[num[j]-1])
                    add(pos[num[j]-1],1);
                if(num[j]<n&&!vis[num[j]+1])
                    add(pos[num[j]+1],1);
                j--;
            }
            ans[query[i].id]=sum(query[i].R)-sum(query[i].L-1);
        }
        for(int i=0;i<m;++i)
           printf("%d\n",ans[i]);
    }
    return 0;
}
