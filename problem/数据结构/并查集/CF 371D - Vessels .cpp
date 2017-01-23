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
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 200000+10;
int a[maxn],sum[maxn],flag[maxn],pa[maxn];
int Find(int x)
{
    return x == pa[x]?x:pa[x] = Find(pa[x]);
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n,m;
    scanf("%d",&n);
    for(int i = 1;i <= n;++i)
        scanf("%d",&a[i]);
    for(int i = 1;i <= n + 1;++i)
        pa[i] = i;
    memset(sum,0,sizeof(sum));
    scanf("%d",&m);
    int type,p,x;
    while(m--)
    {
        scanf("%d",&type);
        if(type == 1)
        {
            scanf("%d%d",&p,&x);
            p = Find(p);
            int tmp;
            while(x && p <= n)
            {
                if(sum[p] < a[p] - x)
                {
                    sum[p] += x;
                    break;
                }
                tmp = a[p] - sum[p];
                x -= tmp;
                sum[p] += tmp;
                pa[p] = p+1;
                p = Find(p);
            }
        }
        else
        {
            scanf("%d",&p);
            printf("%d\n",sum[p]);
        }
    }
    return 0;
}