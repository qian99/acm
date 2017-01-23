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
const int maxn=35;
const ll M=10000000000;
struct BigInt
{
    ll num[150],len;
    void Init(int val)
    {
        memset(num,0,sizeof(num));
        num[0]=val;
        len=1;
    }
    BigInt div2()
    {
        BigInt c;c.Init(0);
        c.num[len-1]=num[len-1]/2;
        for(int i=len-2;i>=0;--i)
        {
            if(num[i+1]&1) c.num[i]=(M+num[i])/2;
            else c.num[i]=num[i]/2;
        }
        c.len=len;
        while(!c.num[c.len-1]&&c.len>1) c.len--;
        return c;
    }
    void ptBigInt()
    {
        printf("%I64d",num[len-1]);
        for(int i=len-2;i>=0;--i)
            printf("%010I64d",num[i]);
        printf("\n");
    }
}res[31][31];
BigInt operator *(const BigInt &a,const int &val)
{
    BigInt c;c.Init(0);
    for(int i=0;i<a.len;++i)
    {
        c.num[i]+=a.num[i]*val;
        if(c.num[i]>=M) {c.num[i+1]+=c.num[i]/M;c.num[i]%=M;}
    }
    c.len=a.len;
    while(c.num[c.len]) {c.num[c.len+1]=c.num[c.len]/M;c.num[c.len++]%=M;}
    return c;
}
BigInt operator +(const BigInt &a,const BigInt &b)
{
    BigInt c;c.Init(0);
    int len=max(a.len,b.len);
    for(int i=0;i<len;++i)
    {
        c.num[i]+=a.num[i]+b.num[i];
        if(c.num[i]>=M) {c.num[i+1]+=c.num[i]/M;c.num[i]%=M;}
    }
    while(c.num[len]) {c.num[len+1]=c.num[len]/M;c.num[len++]%=M;}
    c.len=len;
    return c;
}
int mat[maxn][maxn],ma[maxn][maxn],n,k;
int id[maxn*maxn],c[maxn*maxn];
bool vis[maxn*maxn];
void changes(int type)
{
    if(type==0)
    {
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
                ma[n-j+1][i]=mat[i][j];
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
                mat[i][j]=ma[i][j];
    }
    else if(type==1)
    {
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
                mat[i][j]=ma[j][i];
    }
    else if(type==2)
    {
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
                mat[i][j]=ma[n-j+1][n-i+1];
    }
    else if(type==3)
    {
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
                mat[i][j]=ma[n-i+1][j];
    }
    else
    {
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
                mat[i][j]=ma[i][n-j+1];
    }
}
inline void getid()
{
    int cnt=0;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            id[++cnt]=mat[i][j];
}
void dfs(int u)
{
    if(vis[u]) return ;
    vis[u]=true;
    dfs(id[u]);
}
void solve()
{
    int cnt=0;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            mat[i][j]=++cnt;
    memset(c,0,sizeof(c));
    for(int x=0;x<8;++x)
    {
        if(x<4) changes(0);
        else changes(x-3);
        memset(vis,0,sizeof(vis));
        cnt=0;
        getid();
        for(int i=1;i<=n*n;++i)
        {
            if(!vis[i])
            {
                dfs(i);
                cnt++;
            }
        }
        c[cnt]+=1;
    }
    BigInt tmp;
    res[n][k].Init(0);tmp.Init(k);
    for(int i=1;i<=n*n;++i)
    {
        if(c[i]) res[n][k]=res[n][k]+(tmp*c[i]);
        tmp=tmp*k;
    }
    res[n][k]=res[n][k].div2();
    res[n][k]=res[n][k].div2();
    res[n][k]=res[n][k].div2();
//    res[][].ptBigInt();
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    for(int i=1;i<=30;++i)
        for(int j=1;j<=30;++j)
        {
            n=i;k=j;
            solve();
        }
    while(~scanf("%d%d",&n,&k))
    {
        res[n][k].ptBigInt();
    }
    return 0;
}
