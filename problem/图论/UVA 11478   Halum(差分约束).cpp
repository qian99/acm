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
typedef long long LL;
const int maxn=1000+10;
struct Edge
{
    int from,to,dist;
};
struct BellmanFord
{
    int n,m;
    vector<Edge>edges;
    vector<int>G[maxn];
    int d[maxn],cnt[maxn];
    bool inq[maxn];
    void Init(int n)
    {
        this->n=n;
        for(int i=0;i<n;++i)
           G[i].clear();
        edges.clear();
    }
    void addEdges(int from,int to,int dist)
    {
        edges.push_back((Edge){from,to,dist});
        m=edges.size();
        G[from].push_back(m-1);
    }
    bool negativeCycle()
    {
        queue<int>q;
        memset(inq,0,sizeof(inq));
        memset(cnt,0,sizeof(cnt));
        for(int i=0;i<n;++i)
        {
            d[i]=0;
            q.push(i);
        }
        inq[0]=true;
        while(!q.empty())
        {
            int u=q.front();q.pop();
            inq[u]=false;
            for(int i=0;i<G[u].size();++i)
            {
                Edge x=edges[G[u][i]];
                if(d[x.to]>d[u]+x.dist)
                {
                    d[x.to]=d[u]+x.dist;
                    if(!inq[x.to])
                    {
                        q.push(x.to);
                        inq[x.to]=true;
                        if(++cnt[x.to]>n) return true;
                    }
                }
            }
        }
        return false;
    }
}slover;
bool test(int x)
{
    for(int i=0;i<slover.m;++i)
        slover.edges[i].dist-=x;
    bool flag=slover.negativeCycle();
    for(int i=0;i<slover.m;++i)
        slover.edges[i].dist+=x;
    return flag;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        slover.Init(n);
        int a,b,c;
        int L=0,R=0;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&a,&b,&c);
            a--;b--;
            slover.addEdges(a,b,c);
        }
        if(test(0))
        {
            printf("No Solution\n");
            continue;
        }
        if(!test(10001))
        {
            printf("Infinite\n");
            continue;
        }
        L=1,R=10000;
        while(L<R)
        {
            int m=(L+R)/2;
            if(!test(m))
              L=m+1;
            else
              R=m;
        }
        --L;
        if(L==0)
         printf("No Solution\n");
        else
        printf("%d\n",L);
    }
    return 0;
}
