#include<iostream>
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
const int maxn=100000+10;
vector<int>mat[maxn],g[maxn];
int degree[maxn],ans[maxn],n,m;
void Init()
{
    memset(degree,0,sizeof(degree));
    for(int i=0;i<maxn;++i) mat[i].clear();
    for(int i=0;i<maxn;++i) g[i].clear();
}
void solve()
{
    priority_queue<int,vector<int>,greater<int> >q;
    for(int i=1;i<=n;++i)
        if(degree[i]==0) q.push(i);
    int u,v,size,cnt=0;
    while(!q.empty())
    {
        u=q.top();q.pop();
        ans[cnt++]=u;
        size=g[u].size();
        for(int i=0;i<size;++i)
        {
            v=g[u][i];
            degree[v]--;
            if(degree[v]==0) q.push(v);
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        scanf("%d%d",&n,&m);
        Init();
        int tot,u,size,last;
        bool flag=true;
        for(int i=1;i<=m;++i)
        {
            scanf("%d",&tot);
            while(tot--)
            {
                scanf("%d",&u);
                mat[i].push_back(u);
            }
            size=mat[i].size();
            for(int j=1;j<size;++j)
            {
                if(mat[i][j]<mat[i][j-1]) flag=false;
                g[mat[i][j-1]].push_back(mat[i][j]);
                degree[mat[i][j]]++;
            }
        }
        for(int i=2;i<=m;++i)
        {
            last=mat[i-1].size()-1;
            size=mat[i].size();
            for(int j=size-1;j>=0;--j)
            {
                while(last>=0&&mat[i-1][last]>mat[i][j]) last--;
                if(last==-1) {flag=false;break;}
                g[mat[i][j]].push_back(mat[i-1][last]);
                degree[mat[i-1][last]]++;
                last--;
            }
        }
        printf("Case #%d: ",tcase);
        if(!flag) printf("No solution\n");
        else
        {
            solve();
            for(int i=0;i<n;++i)
            {
                if(i) printf(" ");
                printf("%d",ans[i]);
            }
            printf("\n");
        }
    }
    return 0;
}
