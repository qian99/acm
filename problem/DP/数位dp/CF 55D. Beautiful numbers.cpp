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
const int mod=2520;
ll dp[20][3000][50];
int chf[3000],cht[50];
int num[20];
int gcd(int a,int b)
{
    int c;
    while(b!=0)
    {
        c=a%b;
        a=b;
        b=c;
    }
    return a;
}
int lcm(int a,int b)
{
    return a*b/gcd(a,b);
}
void Init()
{
    int cnt=0;
    for(int i=1;i<=2520;++i)
    {
        if(2520%i==0)
        {
            cht[cnt]=i;
            chf[i]=cnt;
            cnt++;
        }
    }
}
ll dfs(int x,int y,int z)
{
    if(x==0)
    {
        if(y%cht[z]==0) return 1;
        return 0;
    }
    if(dp[x][y][z]>=0) return dp[x][y][z];
    dp[x][y][z]=dfs(x-1,(y*10)%mod,z);
    dp[x][y][z]+=dfs(x-1,(y*10+1)%mod,z);
    int tmp;
    for(int i=2;i<10;++i)
    {
        tmp=lcm(i,cht[z]);
        dp[x][y][z]+=dfs(x-1,(y*10+i)%mod,chf[tmp]);
    }
    return dp[x][y][z];
}
ll solve(int n)
{
    int x=n-1;
    int y=0,z=0;
    ll ans=0;
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<num[i];++j)
        {
            if(j) ans+=dfs(x,(y*10+j)%mod,chf[lcm(j,cht[z])]);
            else ans+=dfs(x,(y*10+j)%mod,z);
        }
        x--;
        y=(y*10+num[i])%mod;
        if(num[i])
        z=chf[lcm(num[i],cht[z])];
    }
    if(y%cht[z]==0) ans++;
    return ans;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    Init();
    memset(dp,0xff,sizeof(dp));
    scanf("%d",&t);
    while(t--)
    {
        ll L,R,ans,tmp;
        int n;
        scanf("%I64d%I64d",&L,&R);
        n=0;
        while(R)
        {
            num[n++]=(R%10);
            R/=10;
        }
        for(int i=0;i<n/2;++i)
        {
            int c=num[i];
            num[i]=num[n-i-1];
            num[n-i-1]=c;
        }
        ans=solve(n);
        n=0;tmp=L;
        bool flag=true;
        while(L)
        {
            num[n++]=(L%10);
            if((L%10)!=0&&tmp%(L%10)) flag=false;
            L/=10;
        }
        for(int i=0;i<n/2;++i)
        {
            int c=num[i];
            num[i]=num[n-i-1];
            num[n-i-1]=c;
        }
        ans-=solve(n);
        if(flag) ans++;
        printf("%I64d\n",ans);
    }
    return 0;
}

