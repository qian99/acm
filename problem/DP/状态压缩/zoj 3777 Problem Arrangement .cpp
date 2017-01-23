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
ll dp[2][1<<12][505];
int val[13][13];
ll gcd(ll a,ll b) {return b==0?a:gcd(b,a%b);}
vector<int>msk[13];
void Init(int n)
{
    int cnt;
    for(int i=0;i<=n;++i) msk[i].clear();
    for(int i=0;i<(1<<n);++i)
    {
        int x=i;
        cnt=0;
        while(x)
        {
            cnt++;
            x=x&(x-1);
        }
        msk[cnt].push_back(i);
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n,m;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        Init(n);
        for(int i=0;i<n;++i)
            for(int j=0;j<n;++j)
                scanf("%d",&val[i][j]);
        dp[0][0][0]=1;
        int tot=1<<n,y,turns,size;
        for(int i=0;i<n;++i)
        {
            turns=i&1;
            size=msk[i+1].size();
            for(int j=0;j<size;++j)
                memset(dp[turns^1][msk[i+1][j]],0,sizeof(dp[turns^1][msk[i+1][j]]));
            size=msk[i].size();
            for(int w=0;w<size;++w)
            {
                int j=msk[i][w];
                for(int x=0;x<=m;++x)
                {
                    if(!dp[turns][j][x]) continue;
                    for(int k=0;k<n;++k)
                    {
                        if(j&(1<<k)) continue;
                        y=x+val[k][i];
                        if(y>m) y=m;
                        dp[turns^1][j|(1<<k)][y]+=dp[turns][j][x];
                    }
                }
            }
        }
        ll Fz=dp[n&1][tot-1][m];
        if(Fz==0)
        {
            printf("No solution\n");
            continue;
        }
        ll Fm=1,tmp;
        for(int i=1;i<=n;++i) Fm*=i;
        tmp=gcd(Fz,Fm);
        Fz/=tmp;Fm/=tmp;
        printf("%lld/%lld\n",Fm,Fz);
    }
    return 0;
}

