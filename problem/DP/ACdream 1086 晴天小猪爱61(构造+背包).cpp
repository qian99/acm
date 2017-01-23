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
#include<bitset>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=10000+10;
int dp[maxn],pre[maxn],num[maxn],tot;
bool check(int x)
{
    int a[10],len=0;
    while(x)
    {
        a[len++]=x%10;
        x/=10;
    }
    for(int i=0;i<len-1;++i)
        if(a[i]==1&&a[i+1]==6)
            return true;
    return false;
}
void Init()
{
    memset(dp,0x3f,sizeof(dp));
    memset(pre,0,sizeof(pre));
    tot=0;
    for(int i=1;i<=6161;++i)
        if(check(i)) num[tot++]=i;
    dp[0]=0;
    for(int i=1;i<=6161;++i)
    {
        for(int j=0;j<tot&&num[j]<=i;++j)
        {
            if(dp[i]>dp[i-num[j]]+1)
            {
                dp[i]=dp[i-num[j]]+1;
                pre[i]=num[j];
            }
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    Init();
    int t,n;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        if(n<=6161)
        {
            if(dp[n]==inf) puts("0");
            else
            {
                printf("%d",dp[n]);
                int now=n;
                while(pre[now])
                {
                    printf(" %d",pre[now]);
                    now=now-pre[now];
                }
                puts("");
            }
        }
        else
        {
            if(check(n))
            {
                printf("1 %d\n",n);
                continue;
            }
            printf("2");
            int a[20],b[20]={0},c[20]={0};
            int len=0;
            while(n)
            {
                a[len++]=n%10;
                n/=10;
            }
            c[0]=1;c[1]=6;
            if(a[0]>=1) b[0]=a[0]-1;
            else a[1]--,b[0]=a[0]+10-1;
            if(a[1]>=6) b[1]=a[1]-6;
            else a[2]--,b[1]=a[1]+10-6;
            b[2]=1;b[3]=6;
            if(a[2]>=1) c[2]=a[2]-1;
            else a[3]--,c[2]=a[2]+10-1;
            if(a[3]>=6) c[3]=a[3]-6;
            else a[4]--,c[3]=a[3]+10-6;
            for(int i=4;i<len;++i)
            {
                if(a[i]<0) {a[i+1]--;a[i]+=10;}
                b[i]=a[i];
            }
            printf(" ");
            while(b[len-1]==0) len--;
            for(int i=len-1;i>=0;--i)
                printf("%d",b[i]);
            printf(" ");
            int i=3;
            while(c[i]==0) i--;
            for(;i>=0;--i) printf("%d",c[i]);
            printf("\n");
        }
    }
    return 0;
}
