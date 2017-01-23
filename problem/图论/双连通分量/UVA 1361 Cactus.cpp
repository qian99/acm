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
#define inf 2139062143
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=20000+10;
//大整数，写的比较挫
struct BigInt
{
    int num[7000];
    int len;
    void clear()
    {
        for(int i=0;i<7000;++i) num[i]=0;
        len=0;
    }
    void getBigInt(ll n)
    {
        clear();
        if(n==0) num[len++]=0;
        while(n!=0)
        {
            num[len++]=n%10;
            n/=10;
        }
    }
    void getBigInt(int n)
    {
        ll m=(ll)n;
        getBigInt(m);
    }
    BigInt operator * (const BigInt a) const
    {
        int m=a.len;
        int n=len;
        BigInt c;
        c.clear();
        int bs=0,w=0,jinwei=0,tp;
        for(int i=0;i<m;++i)
        {
            jinwei=0;
            w=0;
            for(int j=0;j<n;++j)
            {
                tp=a.num[i]*num[j]+jinwei+c.num[bs+w];
                c.num[bs+w]=tp%10;
                jinwei=tp/10;
                w++;
            }
            while(jinwei!=0)
            {
                c.num[bs+w]=jinwei%10;
                jinwei/=10;
                w++;
            }
            c.len=max(c.len,bs+w);
            bs++;
        }
        return c;
    }
};
struct Edge
{
    int u,v;
};
//一大堆数组……
vector<int>G[maxn];
int pre[maxn],ebcno[maxn],bccno[maxn],dfs_clock,ebc_cnt,bcc_cnt;
int parents[maxn],sum;
int pnum[maxn],bnum[maxn],degree[maxn];
ll tmp[maxn];
int top;
BigInt cnt;
stack<int>S;
stack<Edge>SS;
//并查集，用来判图是否连通
int Find(int x)
{
    return x==parents[x]?parents[x]:parents[x]=Find(parents[x]);
}
void Uion(int x,int y)
{
    int a=Find(x);
    int b=Find(y);
    if(a!=b)
    {
        sum++;
        parents[b]=a;
    }
}
//求边连通分量
int dfs(int u,int fa)
{
    int lowu=pre[u]=++dfs_clock;
    S.push(u);
    for(int i=0;i<G[u].size();++i)
    {
        int v=G[u][i];
        if(!pre[v])
        {
            int lowv=dfs(v,u);
            lowu=min(lowu,lowv);
        }
        else if(pre[v]<pre[u]&&v!=fa)
        {
            lowu=min(lowu,pre[v]);
        }
    }
    if(lowu==pre[u])
    {
        ebc_cnt++;
        while(true)
        {
            int x=S.top();S.pop();
            ebcno[x]=ebc_cnt;
            bnum[ebc_cnt]=x;
            if(x==u) break;
        }
    }
    return lowu;
}
void find_ebc(int n)
{
    memset(pre,0,sizeof(pre));
    memset(ebcno,0,sizeof(ebcno));
    while(!S.empty()) S.pop();
    dfs_clock=ebc_cnt=0;
    for(int i=1;i<=n;++i)
       if(!pre[i]) dfs(i,-1);
}
//求点连通分量，将每个点连通分量中边的个数存到数组中
int dfs2(int u,int fa,int ebcnum)
{
    int lowu=pre[u]=++dfs_clock;
    for(int i=0;i<G[u].size();++i)
    {
        int v=G[u][i];
        if(ebcno[v]!=ebcnum) continue;
        Edge e=(Edge){u,v};
        if(!pre[v])
        {
            SS.push(e);
            //sst[top++]=e;
            int lowv=dfs2(v,u,ebcnum);
            lowu=min(lowu,lowv);
            if(lowv>=pre[u])
            {
                bcc_cnt++;
                int sum=0,bs=0;
                while(true)
                {
                    Edge x=SS.top();SS.pop();
                    bs++;
                    if(bccno[x.u]!=bcc_cnt){sum++;bccno[x.u]=bcc_cnt;}
                    if(bccno[x.v]!=bcc_cnt){sum++;bccno[x.v]=bcc_cnt;}
                    if(x.u==u&&x.v==v)
                    {
                        if(sum!=bs) tmp[top++]=0;   //如果边和点的数量不相等，说明不是仙人掌图
                        else
                        tmp[top++]=sum+1;
                        break;
                    }
                }
            }
        }
        else if(pre[v]<pre[u]&&v!=fa)
        {
            SS.push(e);
            lowu=min(lowu,pre[v]);
        }
    }
    return lowu;
}
void find_bcc(int u,int ebcnum)
{
    top=0;
    cnt.getBigInt(1);
    dfs2(u,-1,ebcnum);
    BigInt temp;
    for(int i=0;i<top;++i)
    {
        temp.getBigInt(tmp[i]);
        cnt=cnt*temp;
    }
}
BigInt slove(int n)
{
    find_ebc(n);
    memset(pnum,0,sizeof(pnum));
    memset(degree,0,sizeof(degree));
    for(int u=1;u<=n;++u)
    {
        for(int j=0;j<G[u].size();++j)
        {
            int v=G[u][j];
            if(ebcno[u]==ebcno[v])
            {
                degree[u]++;
                degree[v]++;
            }
        }
    }
    BigInt res;
    res.getBigInt(0);
    for(int u=1;u<=n;++u)
    {
        for(int j=0;j<G[u].size();++j)
        {
            int v=G[u][j];
            if(ebcno[u]==ebcno[v])
            {
                if((degree[u]/2)%2) return res;
                if((degree[v]/2)%2) return res;
            }
        }
    }
    res.getBigInt(1);
    for(int i=1;i<=n;++i)
        pnum[ebcno[i]]++;
    memset(pre,0,sizeof(pre));
    memset(bccno,0,sizeof(bccno));
    dfs_clock=bcc_cnt=0;
    for(int i=1;i<=ebc_cnt;++i)
    {
        if(pnum[i]>=3)
        {
            find_bcc(bnum[i],i);
            res=res*cnt;
        }
    }
    return res;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m,k,tcase=0;
    while(~scanf("%d%d",&n,&m))
    {
        if(tcase++) printf("\n");
        int a,b;
        for(int i=0;i<=n;++i)
        {
            parents[i]=i;
            G[i].clear();
        }
        sum=0;
        while(m--)
        {
            scanf("%d",&k);
            scanf("%d",&a);
            for(int i=1;i<k;++i)
            {
                scanf("%d",&b);
                G[a].push_back(b);
                G[b].push_back(a);
                Uion(a,b);
                a=b;
            }
        }
        BigInt ans;
        if(sum+1!=n) ans.getBigInt(0);
        else ans=slove(n);
        for(int i=ans.len-1;i>=0;--i)
          printf("%d",ans.num[i]);
        printf("\n");
    }
    return 0;
}
