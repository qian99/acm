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
const int maxn=500+10;
const int maxm=1000000+10;
struct Edge
{
    int v,next;
};
struct TwoSat
{
    int n;
    Edge edges[maxm<<1];
    int head[maxn<<1],S[maxn<<1],c,nEdge;
    bool mark[maxn<<1];
    void Init(int n)
    {
        this->n=n;
        memset(head,0xff,sizeof(head));
        memset(mark,0,sizeof(mark));
        nEdge=-1;
    }
    void AddEdge(int u,int v)
    {
        nEdge++;
        edges[nEdge].v=v;
        edges[nEdge].next=head[u];
        head[u]=nEdge;
    }
    void add_clause(int x,int xval,int y,int yval)
    {
        x=x*2+xval;
        y=y*2+yval;
        AddEdge(x^1,y);
        AddEdge(y^1,x);
    }
    bool dfs(int u)
    {
        if(mark[u^1]) return false;
        if(mark[u]) return true;
        S[c++]=u;
        mark[u]=true;
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            int v=edges[k].v;
            if(!dfs(v)) return false;
        }
        return true;
    }
    bool solve()
    {
        for(int i=0;i<n*2;i+=2)
        {
            if(!mark[i]&&!mark[i+1])
            {
                c=0;
                if(!dfs(i))
                {
                    while(c>0) mark[S[--c]]=false;
                    if(!dfs(i+1)) return false;
                }
            }
        }
        return true;
    }
}twosat;
int b[maxn][maxn],p[40];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    for(int i=0;i<31;++i) p[i]=1<<i;
    int n;
    while(~scanf("%d",&n))
    {
        twosat.Init(n*31);
        for(int i=0;i<n;++i)
          for(int j=0;j<n;++j)
            scanf("%d",&b[i][j]);
        bool flag=true;
        for(int i=0;i<n;++i)
          if(b[i][i]) flag=false;
        if(!flag)
        {
            printf("NO\n");
            continue;
        }
        for(int k=0;k<31;++k)
        {
            twosat.Init(n);
            for(int i=0;i<n;++i)
             for(int j=0;j<n;++j)
             {
                 if(i==j) continue;
                 if(i%2==0&&j%2==0)
                 {
                     if(b[i][j]&p[k])
                     {
                         twosat.add_clause(i,1,j,1);
                         twosat.add_clause(i,0,j,1);
                         twosat.add_clause(i,1,j,0);
                     }
                     else twosat.add_clause(i,0,j,0);
                 }
                 else if(i%2==1&&j%2==1)
                 {
                     if(b[i][j]&p[k])
                        twosat.add_clause(i,1,j,1);
                     else
                     {
                         twosat.add_clause(i,0,j,1);
                         twosat.add_clause(i,1,j,0);
                         twosat.add_clause(i,0,j,0);
                     }
                 }
                 else
                 {
                     if(b[i][j]&p[k])
                     {
                         twosat.add_clause(i,1,j,1);
                         twosat.add_clause(i,0,j,0);
                     }
                     else
                     {
                         twosat.add_clause(i,0,j,1);
                         twosat.add_clause(i,1,j,0);
                     }
                 }
             }
            if(!twosat.solve())
            {
                flag=false;
                break;
            }
        }
        if(flag) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
