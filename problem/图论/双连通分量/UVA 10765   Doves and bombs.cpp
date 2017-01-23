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
const int maxn=10000+10;
struct Edge
{
    int u;
    int v;
};
struct Doves
{
    int num;
    int val;
    bool operator < (const Doves a) const
    {
        return (val==a.val&&num<a.num)||val>a.val;
    }
};
int pre[maxn],bccno[maxn],dfs_clock,bcc_cnt;
Doves dove[maxn];
vector<int>G[maxn];
vector<int>bcc[maxn];
stack<Edge>S;
int dfs(int u,int fa)
{
    int lowu=pre[u]=++dfs_clock;
    for(int i=0;i<G[u].size();++i)
    {
        int v=G[u][i];
        Edge e=(Edge){u,v};
        if(!pre[v])
        {
            S.push(e);
            int lowv=dfs(v,u);
            lowu=min(lowu,lowv);
            if(lowv>=pre[u])
            {
                bcc_cnt++;
                bcc[bcc_cnt].clear();
                for(;;)
                {
                    Edge x=S.top();S.pop();
                    if(bccno[x.u]!=bcc_cnt) {bccno[x.u]=bcc_cnt;bcc[bcc_cnt].push_back(x.u);}
                    if(bccno[x.v]!=bcc_cnt) {bccno[x.v]=bcc_cnt;bcc[bcc_cnt].push_back(x.v);}
                    if(x.u==u&&x.v==v) break;
                }
            }
        }
        else if(pre[v]<lowu&&v!=fa)
        {
            S.push(e);
            lowu=min(lowu,pre[v]);
        }
    }
    return lowu;
}
void find_bcc(int n)
{
    memset(pre,0,sizeof(pre));
    memset(bccno,0,sizeof(bccno));
    dfs_clock=bcc_cnt=0;
    for(int i=0;i<n;++i)
    {
        if(!pre[i]) dfs(i,-1);
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        if(n==0&&m==0) break;
        int u,v;
        for(int i=0;i<n;++i)
        {
            G[i].clear();
            dove[i].num=i;
            dove[i].val=0;
        }
        while(~scanf("%d%d",&u,&v))
        {
            if(u==-1&&v==-1) break;
            G[u].push_back(v);
            G[v].push_back(u);
        }
        find_bcc(n);
        for(int i=1;i<=bcc_cnt;++i)
        {
            for(int j=0;j<bcc[i].size();++j)
            {
                int k=bcc[i][j];
                //cout<<k<<" ";
                dove[k].val++;
            }
            //cout<<endl;
        }
        sort(dove,dove+n);
        for(int i=0;i<m;++i)
        {
            printf("%d %d\n",dove[i].num,dove[i].val);
        }
        printf("\n");
    }
    return 0;
}
