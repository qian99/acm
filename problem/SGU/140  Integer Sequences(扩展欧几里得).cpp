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
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=100+10;
void ext_gcd(int a,int b,int & x,int & y,int & d)
{
    if(b==0)
    {
        d=a;x=1;y=0;
        return ;
    }
    ext_gcd(b,a%b,y,x,d);
    y-=(a/b)*x;
}
int A[maxn],X[maxn],Y[maxn],ans[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,p,b;
    scanf("%d%d%d",&n,&p,&b);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&A[i]);
        A[i]%=p;
    }
    A[n+1]=p;
    int k=A[1],d;
    for(int i=1;i<=n;++i)
    {
        ext_gcd(k,A[i+1],X[i],Y[i],d);
        k=d;
    }
    if(b%d)
    {
        printf("NO\n");
    }
    else
    {
        k=b/d;
        Y[0]=1;
        for(int i=n;i>=1;i--)
        {
            k=((X[i]*k)%p+p)%p;
            ans[i]=((Y[i-1]*k)%p+p)%p;
        }
        printf("YES\n");
        for(int i=1;i<=n;++i)
            printf("%d ",ans[i]);
        printf("\n");
    }
    return 0;
}

