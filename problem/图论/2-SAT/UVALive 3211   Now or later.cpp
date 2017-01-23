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
const int maxn=2000+10;
struct TwoSAT
{
    int n;
    vector<int>G[maxn*2];
    bool mark[maxn*2];
    int S[maxn*2],c;
    bool dfs(int u)
    {
        if(mark[u^1]) return false;
        if(mark[u]) return true;
        mark[u]=true;
        S[c++]=u;
        for(int i=0;i<G[u].size();++i)
        {
            if(!dfs(G[u][i])) return false;
        }
        return true;
    }
    void Init(int n)
    {
        this->n=n;
        memset(mark,0,sizeof(mark));
        for(int i=0;i<n*2;++i)
          G[i].clear();
    }
    void add_clause(int x,int xval,int y,int yval)
    {
        x=x*2+xval;
        y=y*2+yval;
        G[x^1].push_back(y);
        G[y^1].push_back(x);
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
};
TwoSAT solver;
int T[maxn][2],n;
bool test(int P)
{
    solver.Init(n);
    for(int i=0;i<n;++i)
    {
        for(int j=i+1;j<n;++j)
        {
            if(abs(T[i][0]-T[j][0])<P) solver.add_clause(i,1,j,1);
            if(abs(T[i][0]-T[j][1])<P) solver.add_clause(i,1,j,0);
            if(abs(T[i][1]-T[j][0])<P) solver.add_clause(i,0,j,1);
            if(abs(T[i][1]-T[j][1])<P) solver.add_clause(i,0,j,0);
        }
    }
    return solver.solve();
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int maxt;
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        maxt=0;
        for(int i=0;i<n;++i)
        {
            scanf("%d%d",&T[i][0],&T[i][1]);
            maxt=max(T[i][0],maxt);
            maxt=max(T[i][1],maxt);
        }
        int L=0,R=maxt;
        while(L<R)
        {
            int m=L+(R-L+1)/2;
            if(test(m))
               L=m;
            else
               R=m-1;
        }
        printf("%d\n",L);
    }
    return 0;
}
