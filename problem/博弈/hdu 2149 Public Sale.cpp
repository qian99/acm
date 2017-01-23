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
const int maxn=1000+300;
int flag[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d%d",&m,&n))
    {
        memset(flag,0,sizeof(flag));
        int t=m;
        while(t>0)
        {
            flag[t]=true;
            t-=(n+1);
        }
        if(n>m)
          for(int i=m;i<=n;++i) flag[i]=true;
        bool ff=false;
        for(int i=1;i<=n;++i)
        {
            if(flag[i])
            {
                if(!ff)
                {
                    ff=true;
                    printf("%d",i);
                }
                else printf(" %d",i);
            }
        }
        if(ff) printf("\n");
        else printf("none\n");
    }
    return 0;
}
