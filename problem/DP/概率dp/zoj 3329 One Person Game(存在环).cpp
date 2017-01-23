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
const int maxn=500+100;
double A[maxn],B[maxn],p;
bool flag[maxn];
int a,b,c,n,k1,k2,k3;
void f(int x)
{
    if(x>n) {A[x]=B[x]=0;return ;}
    if(flag[x]) return ;
    flag[x]=true;
    A[x]=p;B[x]=1;
    for(int i=1;i<=k1;++i)
        for(int j=1;j<=k2;++j)
            for(int k=1;k<=k3;++k)
            {
                if(i==a&&j==b&&k==c) continue;
                f(x+i+j+k);
                A[x]+=p*A[x+i+j+k];
                B[x]+=p*B[x+i+j+k];
            }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d%d%d%d%d%d",&n,&k1,&k2,&k3,&a,&b,&c);
        memset(flag,0,sizeof(flag));
        p=1.0/k1/k2/k3;
        f(0);
        printf("%.16lf\n",B[0]/(1-A[0]));
    }
    return 0;
}
