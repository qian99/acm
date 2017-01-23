#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<set>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=35;
const int mod=1000000007;
int dp[maxn][2][2][2][2],sum[maxn][2][2][2][2];
int num[maxn][4];
ll p[maxn];
int f(int pos,int a,int b,int c,int d,int &tot)
{
    if(pos==-1) {tot=1;return 0;}
    if(dp[pos][a][b][c][d]!=-1)
    {
        tot=sum[pos][a][b][c][d];
        return dp[pos][a][b][c][d];
    }
    int &res=dp[pos][a][b][c][d]=0;
    int &cnt=sum[pos][a][b][c][d]=0;
    int ea=a?num[pos][0]:1,eb=b?num[pos][1]:1;
    int ec=c?num[pos][2]:1,ed=d?num[pos][3]:1;
    int tmp1,tmp2;
    for(int i=0;i<=ea;++i)
        for(int j=0;j<=eb;++j)
            for(int k=0;k<=ec;++k)
                for(int x=0;x<=ed;++x)
                {
                    if(i^j^k^x) continue;
                    tmp1=f(pos-1,a&&i==ea,b&&j==eb,c&&k==ec,d&&x==ed,tmp2);
                    res=(res+tmp1+tmp2*p[pos]*(i+j+k+x))%mod;
                    cnt+=tmp2;
                    if(cnt>=mod) cnt-=mod;
                }
    tot=cnt;
    return res;
}
int cal(int A[4],int &cnt)
{
    memset(dp,0xff,sizeof(dp));
    for(int i=0;i<4;++i)
        for(int j=30;j>=0;--j)
        {
            if(A[i]&(1<<j)) num[j][i]=1;
            else num[j][i]=0;
        }
    return f(30,1,1,1,1,cnt);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    p[0]=1;
    for(int i=1;i<maxn;++i) p[i]=p[i-1]*2%mod;
    int L[4],R[4],A[4];
    while(~scanf("%d%d%d%d%d%d%d%d",&L[0],&R[0],&L[1],&R[1],&L[2],&R[2],&L[3],&R[3]))
    {
        for(int i=0;i<4;++i) L[i]--;
        int Sum=0,Count=0;
        int tmp1,tmp2,tot;
        for(int i=0;i<16;++i)
        {
            tot=0;
            for(int j=0;j<4;++j)
                if((i>>j)&1) A[j]=R[j],tot^=1;
                else A[j]=L[j];
            tmp1=cal(A,tmp2);
            if(tot&1)
            {
                Sum-=tmp1;
                if(Sum<0) Sum+=mod;
                Count-=tmp2;
                if(Count<0) Count+=mod;
            }
            else
            {
                Sum+=tmp1;
                if(Sum>=mod) Sum-=mod;
                Count+=tmp2;
                if(Count>=mod) Count-=mod;
            }
        }
        printf("%d %d\n",Count,Sum);
    }
    return 0;
}
