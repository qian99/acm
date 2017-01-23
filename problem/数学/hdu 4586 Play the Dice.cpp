#include <iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d",&n))
    {
        double sum=0;
        int tmp;
        for(int i=0;i<n;++i)
        {
            scanf("%d",&tmp);
            sum+=tmp;
        }
        scanf("%d",&m);
        for(int i=0;i<m;++i)
            scanf("%d",&tmp);
        if(m==n&&sum==0)
        {
            printf("0\n");
            continue;
        }
        if(m==n&&sum!=0)
        {
            printf("inf\n");
            continue;
        }
        double res=sum/(n-m);
        printf("%.2lf\n",res);
    }
    return 0;
}
