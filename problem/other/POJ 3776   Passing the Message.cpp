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
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
const int maxn=50000+10;
int lf[maxn],rn[maxn],num[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        tcase++;
        for(int i=1;i<=n;++i)
          scanf("%d",&num[i]);
        num[n+1]=num[0]=inf;
        lf[0]=1;
        rn[n+1]=n;
        int p;
        for(int i=1;i<=n;++i)
        {
            p=i;
            lf[i]=i;
            while(num[i]>num[p-1])
            {
                lf[i]=lf[p-1];
                p=lf[p-1];
            }
        }
        for(int i=n;i>=1;--i)
        {
            p=i;
            rn[i]=i;
            while(num[i]>num[p+1])
            {
                rn[i]=rn[p+1];
                p=rn[p+1];
            }
        }
        int ul,ur,pl,pr;
        printf("Case %d:\n",tcase);
        for(int i=1;i<=n;++i)
        {
            ul=i-1;
            ur=i+1;
            pl=pr=0;
            if(lf[i]!=i&&i-1!=0)
            {
                pl=ul;
                while(lf[ul]!=lf[i])
                {
                    if(ul==lf[ul])
                      ul--;
                    else
                      ul=lf[ul]-1;
                    pl=ul;
                }
            }
            if(rn[i]!=i&&i!=n)
            {
                pr=ur;
                while(rn[ur]!=rn[i])
                {
                    if(ur==rn[ur])
                       ur++;
                    else
                       ur=rn[ur]+1;
                    pr=ur;
                }
            }
            printf("%d %d\n",pl,pr);
        }
    }
    return 0;
}
