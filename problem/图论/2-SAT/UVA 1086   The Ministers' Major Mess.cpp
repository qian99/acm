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
const int maxn=100+10;
struct TwoSAT
{
    int n;
    vector<int>G[maxn*2];
    bool mark[maxn*2],must[maxn*2];
    int S[maxn*2],c;
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
    void dfs2(int u)
    {
        must[u]=true;
        for(int i=0;i<G[u].size();++i)
          if(!must[G[u][i]]) dfs2(G[u][i]);
    }
    void Init(int n)
    {
        this->n=n;
        for(int i=0;i<n*2;++i) G[i].clear();
        memset(mark,0,sizeof(mark));
        memset(must,0,sizeof(must));
    }
    void clear()
    {
        memset(mark,0,sizeof(mark));
        for(int i=0;i<n*2;++i)
          mark[i]=must[i];
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
            if(mark[i]&&mark[i+1]) return false;
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
int ans[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m,k,tcase=0;
    while(~scanf("%d%d",&n,&m))
    {
        if(n==0&&m==0) break;
        tcase++;
        slover.Init(n);
        memset(ans,0,sizeof(ans));
        char c[10][10];
        int x,y,v[10];
        while(m--)
        {
            scanf("%d",&k);
            for(int i=0;i<k;++i)
               scanf("%d%s",&v[i],c[i]);
            if(k>=3)
            {
                for(int i=0;i<k;++i)
                {
                    for(int j=i+1;j<k;++j)
                    {
                        x=c[i][0]=='y'?1:0;
                        y=c[j][0]=='y'?1:0;
                        slover.add_clause(v[i]-1,x,v[j]-1,y);
                    }
                }
            }
            else
            {
                for(int i=0;i<k;++i)
                {
                    x=c[i][0]=='y'?1:0;
                    slover.must[(v[i]-1)*2+x]=true;
                }
            }
        }
        for(int i=0;i<n*2;++i)
            if(slover.must[i]) slover.dfs2(i);
        for(int i=0;i<n;i++)
        {
            if(slover.must[i*2]||slover.must[i*2+1]) continue;
            slover.clear();
            slover.mark[i*2]=true;
            bool f1=slover.slove();
            slover.clear();
            slover.mark[i*2+1]=true;
            bool f2=slover.slove();
            if(f1&&f2) ans[i]=1;
        }
        slover.clear();
        printf("Case %d: ",tcase);
        if(!slover.slove())
            printf("impossible\n");
        else
        {
            for(int i=0;i<n;++i)
            {
                if(ans[i]) printf("?");
                else if(slover.mark[i*2]) printf("n");
                else printf("y");
            }
            printf("\n");
        }
    }
    return 0;
}
