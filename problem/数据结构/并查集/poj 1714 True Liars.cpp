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
const int maxn=600+10;
int parents[maxn],rt[maxn];
int con[maxn],cnt[maxn],diff[maxn],ron[maxn];
int ans[maxn];
int dp[maxn][maxn];
int Find(int x)
{
    if(x==parents[x]) return x;
    int tmp=parents[x];
    Find(parents[x]);
    rt[x]=rt[tmp]^rt[x];
    parents[x]=parents[tmp];
    return parents[x];
}
void Uion(int x,int y,int v)
{
    int a=Find(x);
    int b=Find(y);
    if(a!=b)
    {
        if(v)
        {
            rt[b]=rt[x]^rt[y]^v;
            parents[b]=a;
        }
        else
        {
            rt[b]=rt[x]^rt[y];
            parents[b]=a;
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,p1,p2;
    int x,y;
    char str[5];
    while(~scanf("%d%d%d",&n,&p1,&p2))
    {
        if(n==0&&p1==0&&p2==0) break;
        int m=p1+p2;
        for(int i=1;i<=m;++i) parents[i]=i,rt[i]=0;
        memset(con,0,sizeof(con));
        memset(cnt,0,sizeof(cnt));
        memset(diff,0,sizeof(diff));
        memset(dp,0,sizeof(dp));
        for(int i=0;i<n;++i)
        {
            scanf("%d%d%s",&x,&y,str);
            if(str[0]=='y') Uion(x,y,0);
            else Uion(x,y,1);
        }
        for(int i=1;i<=m;++i) Find(i);
        int k=0,pa;
        for(int i=1;i<=m;++i)
        {
            pa=parents[i];
            if(con[pa]==0)
            {
                con[pa]=++k;
                ron[k]=pa;
            }
            cnt[con[pa]]++;
            if(rt[i]) diff[con[pa]]++;
        }
        dp[0][0]=1;
        bool flag=true;
        for(int i=1;i<=k;++i)
        {
            x=diff[i];y=cnt[i]-diff[i];
            if(x==y) flag=false;
            for(int j=m;j>=x;--j)
              dp[i][j]+=dp[i-1][j-x];
            for(int j=m;j>=y;--j)
              dp[i][j]+=dp[i-1][j-y];
        }
        if(dp[k][p1]!=1||!flag)
          printf("no\n");
        else
        {
            int now=p1;
            for(int i=k;i>=1;--i)
            {
                x=diff[i];y=cnt[i]-diff[i];
                if(dp[i-1][now-x]==1)
                {
                    ans[ron[i]]=1;
                    now-=x;
                }
                else if(dp[i-1][now-y]==1)
                {
                    ans[ron[i]]=0;
                    now-=y;
                }
            }
            for(int i=1;i<=m;++i)
            {
                pa=parents[i];
                if(ans[pa]==rt[i])
                 printf("%d\n",i);
            }
            printf("end\n");
        }
    }
    return 0;
}
