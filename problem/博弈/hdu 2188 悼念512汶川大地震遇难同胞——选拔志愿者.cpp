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
const int maxn=10000+300;
int flag[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&m,&n);
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
                ff=true;
                break;
            }
        }
        if(ff) printf("Grass\n");
        else printf("Rabbit\n");
    }
    return 0;
}
