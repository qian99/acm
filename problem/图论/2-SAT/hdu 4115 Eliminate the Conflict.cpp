#include <iostream>
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
int w[maxn];
struct TwoSAT
{
    int n;
    vector<int>G[maxn*6];
    bool mark[maxn*6];
    int S[maxn*6],c;
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
}solver;
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
        solver.Init(n*3);
        for(int i=0;i<n;++i)
          scanf("%d",&w[i]);
        for(int i=0;i<n;i++)
        {
            solver.add_clause(i*3,0,i*3+1,0);
            solver.add_clause(i*3+1,0,i*3+2,0);
            solver.add_clause(i*3+2,0,i*3,0);
        }
        int a,b,k;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&a,&b,&k);
            a--;b--;
            if(k==0)
            {

                a*=3;b*=3;
                solver.add_clause(a,0,b,1);
                solver.add_clause(a,1,b,0);
                solver.add_clause(a+1,0,b+1,1);
                solver.add_clause(a+1,1,b+1,0);
                solver.add_clause(a+2,0,b+2,1);
                solver.add_clause(a+2,1,b+2,0);
            }
            else
            {
                a*=3;b*=3;
                solver.add_clause(a,0,b,0);
                solver.add_clause(a+1,0,b+1,0);
                solver.add_clause(a+2,0,b+2,0);
            }
        }
        for(int i=0;i<n;++i)
        {
            a=i*3;
            if(w[i]==1)
                solver.add_clause(a,1,a+1,1);
            else if(w[i]==2)
                solver.add_clause(a+1,1,a+2,1);
            else
                solver.add_clause(a+2,1,a,1);
        }
        printf("Case #%d: ",tcase);
        if(solver.solve())
          puts("yes");
        else puts("no");
    }
    return 0;
}
