#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 1e5+10;
int a[maxn],num[maxn];
int dcmp(double x) {return (x>eps)-(x<-eps);}
int gcd(int a,int b)
{
    return b==0?a:gcd(b,a%b);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,k,p;
    while(~scanf("%d%d%d",&n,&k,&p))
    {
        ll sum=0;
        int cnt=1;
        memset(num,0,sizeof(num));
        for(int i=1;i<=n-k;++i)
        {
            a[i]=1;
            sum+=a[i];
            num[cnt]++;
        }
        cnt=2;
        for(int i=n-k+1;i<=n;++i)
        {
            int d=gcd(i-1,100);
            d=100*(i-1)/d;
            int tmp=i-1-num[cnt];
            if(tmp*(d/(i-1))>=p*(d/100))
            {
                a[i]=cnt;
                num[cnt]++;
                sum+=cnt;
            }
            else
            {
                cnt++;
                num[cnt]++;
                a[i]=cnt;
                sum+=cnt;
            }
        }
        printf("%I64d\n",sum);
        printf("%d",a[1]);
        for(int i=2;i<=n;++i)
          printf(" %d",a[i]);
        printf("\n");
    }
    return 0;
}
