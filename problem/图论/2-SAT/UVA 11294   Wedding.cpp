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
const int maxn=100;
struct TwoSAT
{
    int n;
    vector<int>G[maxn*2];
    int S[maxn*2],c;
    bool mark[maxn*2];
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
    int m,n;
    while(~scanf("%d%d",&n,&m))
    {
        if(m==0&&n==0) break;
        int a,b,x,y;
        char c,d;
        slover.Init(n);
        for(int i=0;i<m;++i)
        {
            scanf("%d%c %d%c",&a,&c,&b,&d);
            x=(c=='h')?0:1;
            y=(d=='h')?0:1;
            slover.add_clause(a,x,b,y);
        }
        slover.G[0].push_back(1);
        if(slover.slove())
        {
            for(int i=1;i<n;++i)
            {
                if(i>1) printf(" ");
                if(slover.mark[i*2]!=slover.mark[0])
                  printf("%dh",i);
                else
                  printf("%dw",i);
            }
            printf("\n");
        }
        else
        {
            printf("bad luck\n");
        }
    }
    return 0;
}
