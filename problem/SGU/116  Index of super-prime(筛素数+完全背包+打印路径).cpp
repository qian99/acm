#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<cmath>
#include<vector>
#include<queue>
#include<stack>
using namespace std;
typedef long long ll;
const int maxn=10000+10;
bool flag[maxn];
int primes[maxn],sprimes[maxn],p,sp;
int paths[maxn];
int dp[maxn];
void getprime()
{
    p=1;
    memset(flag,0,sizeof(flag));
    flag[0]=flag[1]=true;
    for(int i=2;i<maxn;++i)
    {
        if(!flag[i])
        {
            primes[p++]=i;
            for(int j=i*2;j<maxn;j+=i)
              flag[j]=true;
        }
    }
    sp=0;
    for(int i=1;i<p;++i)
      if(!flag[i]&&primes[i]<=10000) sprimes[sp++]=primes[i];
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    getprime();
    memset(dp,0xff,sizeof(dp));
    dp[0]=0;
    for(int i=0;i<sp;++i)
    {
        for(int j=0;j<maxn-sprimes[i];j++)
          if(dp[j]!=-1)
          {
              if(dp[j+sprimes[i]]==-1)
                dp[j+sprimes[i]]=dp[j]+1;
              else dp[j+sprimes[i]]=min(dp[j+sprimes[i]],dp[j]+1);
          }
    }
    int n;
    while(~scanf("%d",&n))
    {
        if(dp[n]==-1)
        {
            printf("0\n");
            continue;
        }
        int cnt=0;
        int k=sp-1;
        while(n)
        {
            for(;k>=0;--k)
            {
                if(sprimes[k]>n) continue;
                if(dp[n-sprimes[k]]!=-1&&dp[n-sprimes[k]]+1==dp[n])
                {
                    paths[cnt++]=sprimes[k];
                    n-=sprimes[k];
                    break;
                }
            }
        }
        sort(paths,paths+cnt);
        printf("%d\n",cnt);
        for(int i=cnt-1;i>=0;--i)
        {
            printf("%d",paths[i]);
            if(i) printf(" ");
        }
        printf("\n");
    }
    return 0;
}
