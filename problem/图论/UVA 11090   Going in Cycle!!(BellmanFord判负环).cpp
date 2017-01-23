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
const int maxn=500+10;
struct Edge
{
    int from,to;
    double dist;
};
struct BellmanFord
{
    int n,m;
    vector<Edge>edges;
    vector<int>G[maxn];
    bool inq[maxn];
    double d[maxn];
    int p[maxn],cnt[maxn];
    void Init(int n)
    {
        this->n=n;
        for(int i=0;i<n;++i) G[i].clear();
        edges.clear();
    }
    void addEdge(int from,int to,double dist)
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
            d[i]=inf;inq[0]=true;
            q.push(i);
        }
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
                    p[x.to]=G[u][i];
                    if(!inq[x.to]){q.push(x.to);inq[x.to]=true;if(++cnt[x.to]>n) return true;}
                }
            }
        }
        return false;
    }
}slover;
bool test(double x)
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
    int t,n,m,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        scanf("%d%d",&n,&m);
        int a,b,c;
        int maxv=0;
        slover.Init(n);
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&a,&b,&c);
            a--;b--;
            maxv=max(maxv,c);
            slover.addEdge(a,b,c);
        }
        printf("Case #%d: ",tcase);
        double L=0,R=maxv;
        if(!test(maxv+1))
        {
            printf("No cycle found.\n");
            continue;
        }
        while(R-L>1e-3)
        {
            double m=(R+L)/2;
            if(test(m))
            {
                R=m;
            }
            else
            {
                L=m;
            }
        }
        printf("%.2lf\n",L);
    }
    return 0;
}
