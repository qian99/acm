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
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 10000 + 10;
int cnt[maxn],val[maxn];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t,tcase = 0;
    scanf("%d",&t);
    while(t--)
    {
        int n,m = 0,maxv = 0,tot = 0,a;
        memset(cnt,0,sizeof(cnt));
        scanf("%d",&n);
        for(int i = 0;i < n;++i)
        {
            scanf("%d",&a);
            if(cnt[10000 - (100 - a)*(100 - a)] == 0)
                tot++;
            cnt[10000 - (100 - a)*(100 - a)]++;
        }
        for(int i = 0;i <= 10000;++i)
        {
            if(!cnt[i]) continue;
            if(cnt[i] > maxv)
            {
                maxv = cnt[i];
                m = 0;
                val[m++] = i;
            }
            else if(cnt[i] == maxv)
                val[m++] = i;
        }
        printf("Case #%d:\n",++tcase);
        if(m == tot && tot != 1)
            puts("Bad Mushroom");
        else
        {
            for(int i = 0;i < m;++i)
            {
                if(i) printf(" ");
                printf("%d",val[i]);
            }
            puts("");
        }
    }
    return 0;
}
