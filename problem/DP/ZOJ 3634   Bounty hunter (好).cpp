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
const int maxn=100000+10;
//mon[i]表示带1元钱进入城市i能获得的最多的金钱
//att[i]表示带1点攻击力进入城市i能获得的最多的金钱
double mon[maxn],att[maxn],a[maxn],b[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,x,y;
    while(~scanf("%d%d%d",&n,&x,&y))
    {
        for(int i=1;i<=n;++i)
            scanf("%lf%lf",&a[i],&b[i]);
        att[n]=b[n];
        mon[n]=max(1.0,1/a[n]*b[n]);
        for(int i=n-1;i>=1;--i)
        {
            att[i]=mon[i+1]*b[i]+att[i+1];
            mon[i]=max(mon[i+1],1/a[i]*(mon[i+1]*b[i]+att[i+1]));
        }
        printf("%.2lf\n",x*mon[1]+y*att[1]);
    }
    return 0;
}
