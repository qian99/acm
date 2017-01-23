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
const int maxn=60000+10;
int pre[maxn],iscut[maxn],bccno[maxn],dfs_clock,bcc_cnt;
struct Edge
{
    int u;
    int v;
};
vector<int>G[maxn],bcc[maxn];
stack<Edge>S;
int dfs(int u,int fa)
{
    int lowu=pre[u]=++dfs_clock;
    int child=0;
    int sz=G[u].size();
    for(int i=0;i<sz;++i)
    {
        int v=G[u][i];
        Edge e=(Edge){u,v};
        if(!pre[v])
        {
            child++;
            S.push(e);
            int lowv=dfs(v,u);
            lowu=min(lowu,lowv);
            if(lowv>=pre[u])
            {
                iscut[u]=true;
                bcc_cnt++;bcc[bcc_cnt].clear();
                for(;;)
                {
                    Edge x=S.top();S.pop();
                    if(bccno[x.u]!=bcc_cnt){bccno[x.u]=bcc_cnt;bcc[bcc_cnt].push_back(x.u);}
                    if(bccno[x.v]!=bcc_cnt){bccno[x.v]=bcc_cnt;bcc[bcc_cnt].push_back(x.v);}
                    if(x.u==u&&x.v==v) break;
                }
            }
        }
        else if(pre[v]<pre[u]&&v!=fa)
        {
            S.push(e);
            lowu=min(lowu,pre[v]);
        }
    }
    if(fa<0&&child==1) iscut[u]=0;
    return lowu;
}
void find_bcc(int n)
{
    memset(pre,0,sizeof(pre));
    memset(iscut,0,sizeof(iscut));
    memset(bccno,0,sizeof(bccno));
    dfs_clock=bcc_cnt=0;
    for(int i=1;i<=n;++i)
    {
        if(!pre[i]) dfs(i,-1);
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int size = 256 << 20; // 256MB
    char *p = (char*)malloc(size) + size;
    __asm__("movl %0, %%esp\n" :: "r"(p) );
    int m,n;
    int tcase=0;
    while(~scanf("%d",&m))
    {
        if(m==0) break;
        tcase++;
        int n=0;
        int a,b;
        for(int i=0;i<maxn;++i)
           G[i].clear();
        map<int,int>mp;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d",&a,&b);
            if(mp[a]==0)
              mp[a]=++n;
            if(mp[b]==0)
              mp[b]=++n;
            G[mp[a]].push_back(mp[b]);
            G[mp[b]].push_back(mp[a]);
        }
        find_bcc(n);
        long long ans1=0,ans2=1;
        for(int i=1;i<=bcc_cnt;++i)
        {
            int cut_cnt=0;
            int sz=bcc[i].size();
            for(int j=0;j<sz;++j)
               if(iscut[bcc[i][j]]) cut_cnt++;
            if(cut_cnt==1)
            {
                ans1++;
                ans2*=(long long)(bcc[i].size()-cut_cnt);
            }
        }
        if(bcc_cnt==1)
        {
            ans1=2;
            ans2=bcc[1].size()*(bcc[1].size()-1)/2;
        }
        printf("Case %d: %I64d %I64d\n",tcase,ans1,ans2);
    }
    return 0;
}
