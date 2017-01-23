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
const int maxn=3000+10;
struct TwoSAT
{
    int n;
    vector<int>G[maxn<<1];
    bool mark[maxn<<1];
    int S[maxn<<1],c;
    void Init(int n)
    {
        this->n=n;
        for(int i=0;i<n*2;++i)
           G[i].clear();
        memset(mark,0,sizeof(mark));
    }
    bool dfs(int u)
    {
        if(mark[u^1]) return false;
        if(mark[u]) return true;
        mark[u]=true;
        S[c++]=u;
        for(int i=0;i<G[u].size();++i)
           if(!dfs(G[u][i])) return false;
        return true;
    }
    void add_clause(int x,int xval,int y,int yval)
    {
        x=2*x+xval;
        y=2*y+yval;
        G[x^1].push_back(y);
        G[y^1].push_back(x);
    }
    bool slove()
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
}slover;
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        int x,y,z;
        slover.Init(n*3);
        for(int i=0;i<n;++i)
        {
            scanf("%d%d%d",&x,&y,&z);
            slover.add_clause(x,1,y,1);
            slover.add_clause(x,1,z,1);
            slover.add_clause(x,0,y,0);
            slover.add_clause(x,0,z,0);
            slover.add_clause(y,0,z,1);
            slover.add_clause(y,1,z,0);
        }
        for(int i=0;i<m;++i)
        {
            scanf("%d%d",&x,&y);
            slover.add_clause(x,0,y,0);
            slover.add_clause(y,0,x,0);
        }
        if(slover.slove())
          puts("yes");
        else
          puts("no");
    }
    return 0;
}
