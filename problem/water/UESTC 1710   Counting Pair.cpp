#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<cstdio>
#include<cmath>
#include<map>
#include<queue>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n,m,q,k,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        scanf("%d%d",&n,&m);
        scanf("%d",&q);
        printf("Case #%d:\n",tcase);
        for(int i=0;i<q;++i)
        {
            scanf("%d",&k);
            int a=min(k-1,n);
            int b=min(k-1,m);
            b=(k-1)-b;
            if(a-b<0)
            printf("0\n");
            else
            printf("%d\n",a-b);
        }
    }
    return 0;
}
