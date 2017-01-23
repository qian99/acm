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
struct TwoSAT
{
    int n;
    vector<int>G[maxn<<1];
    bool mark[maxn<<1];
    int S[maxn<<1],c;
    void Init(int n)
    {
        this->n=n;
        for(int i=0;i<n*2;++i) G[i].clear();
        memset(mark,0,sizeof(mark));
    }
    bool dfs(int u)
    {
        if(mark[u^1]) return false;
        if(mark[u]) return true;
        S[c++]=u;
        mark[u]=true;
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
        for(int i=0;i<2*n;i+=2)
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
    while(~scanf("%d",&n))
    {
        scanf("%d",&m);
        slover.Init(n);
        int x,y,xval,yval;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d%d",&x,&y,&xval,&yval);
            slover.add_clause(x,xval^1,y,yval^1);
        }
        if(slover.slove())
           printf("YES\n");
        else
           printf("NO\n");
    }
    return 0;
}

