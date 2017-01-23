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
typedef long long ll;
const int maxn=1000+10;
char sa[maxn],sb[maxn],sc[maxn];
int dp[maxn][maxn],dp2[maxn][maxn],lenA,lenB,lenC;
int startA[maxn],endA[maxn],startB[maxn],endB[maxn];
void lcs()
{
    for(int i=1;i<=lenA;++i)
    {
        for(int j=1;j<=lenB;++j)
        {
            if(sa[i]==sb[j])
               dp[i][j]=dp[i-1][j-1]+1;
            else dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
        }
    }
}
void lcs2()
{
    for(int i=lenA;i>=1;i--)
    {
        for(int j=lenB;j>=1;--j)
        {
            if(sa[i]==sb[j]) dp2[i][j]=dp2[i+1][j+1]+1;
            else dp2[i][j]=max(dp2[i][j+1],dp2[i+1][j]);
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
        scanf("%s%s%s",sa+1,sb+1,sc+1);
        memset(dp,0,sizeof(dp));
        memset(dp2,0,sizeof(dp2));
        lenA=strlen(sa+1),lenB=strlen(sb+1),lenC=strlen(sc+1);
        lcs();
        lcs2();
        int m=0,n=0;
        for(int i=1;i<=lenA;++i)
        {
            if(sa[i]==sc[1])
            {
                int j=i,k=1;
                for(;j<=lenA&&k<=lenC;++j)
                  if(sa[j]==sc[k]) k++;
                if(k!=lenC+1) break;
                startA[m]=i;
                endA[m++]=j-1;
            }
        }
        for(int i=1;i<=lenB;++i)
        {
            if(sb[i]==sc[1])
            {
                int j=i,k=1;
                for(;j<=lenB&&k<=lenC;++j)
                  if(sb[j]==sc[k]) k++;
                if(k!=lenC+1) break;
                startB[n]=i;
                endB[n++]=j-1;
            }
        }
        int ans=0;
        for(int i=0;i<m;++i)
            for(int j=0;j<n;++j)
                ans=max(ans,dp[startA[i]-1][startB[j]-1]+dp2[endA[i]+1][endB[j]+1]);
              //ans=max(ans,lcs(startA[i],endA[i],startB[j],endB[j]));
        printf("Case #%d: %d\n",tcase,ans+lenC);
    }
    return 0;
}
