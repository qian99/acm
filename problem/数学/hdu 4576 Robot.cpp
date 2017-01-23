#include <iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=200+10;
double p[2][maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m,l,r,w;
    while(~scanf("%d%d%d%d",&n,&m,&l,&r))
    {
        if(n==0&&m==0&&l==0&&r==0) break;
        int rnd=0;
        memset(p,0,sizeof(p));
        p[0][1]=1;
        int z=min(m,10000);
        int last=max(0,m-z);
        int f,t;
        for(int i=0;i<z;++i)
        {
            scanf("%d",&w);
            for(int j=1;j<=n;++j)
            {
                f=(((j-w)%n)+n)%n;
                if(f==0) f=n;
                t=(j+w)%n;
                if(t==0) t=n;
                p[rnd^1][f]+=p[rnd][j]*0.5;
                p[rnd^1][t]+=p[rnd][j]*0.5;
                p[rnd][j]=0;
            }
            rnd^=1;
        }
        for(int i=0;i<last;++i)
           scanf("%d",&w);
        double res=0;
        for(int i=l;i<=r;++i)
           res+=p[rnd][i];
        printf("%.4lf\n",res);
    }
    return 0;
}
