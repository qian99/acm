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
const int maxn=300+10;
int a[maxn][maxn],sum[maxn][maxn];
int gcd(int a,int b) { return b==0?a:gcd(b,a%b); }
void Init()
{
    memset(a,0,sizeof(a));
    memset(sum,0,sizeof(sum));
    for(int i=1;i<maxn;++i)
        for(int j=1;j<maxn;++j)
        {
            int tmp=gcd(i,j);
            if(tmp==1)
                a[i][j]=1;
            else if(tmp==2)
                a[i][j]=-1;
        }
    for(int i=1;i<maxn;++i)
        for(int j=1;j<maxn;++j)
            a[i][j]+=a[i][j-1];
    for(int i=1;i<maxn;++i)
        for(int j=1;j<maxn;++j)
            a[i][j]+=a[i-1][j];
    for(int i=1;i<maxn;++i)
        for(int j=1;j<maxn;++j)
            sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+a[i][j];
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    Init();
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        if(n==0&&m==0) break;
        n--;m--;
        printf("%d\n",sum[n][m]*2);
    }
    return 0;
}
