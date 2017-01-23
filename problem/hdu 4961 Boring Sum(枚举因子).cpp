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
const int maxn = 100000+10;
vector<int>factor[maxn];
int a[maxn],b[maxn],c[maxn];
vector<int>vt[maxn];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    for(int i = 1;i < maxn;++i)
        for(int j = i;j < maxn ; j += i)
            factor[j].push_back(i);
    int n;
    while(~scanf("%d",&n))
    {
        if(n == 0) break;
        int maxv = 0;
        for(int i = 1;i <= n;++i)
        {
            scanf("%d",&a[i]);
            if(maxv < a[i]) maxv = a[i];
        }
        for(int i = 1;i <= maxv ; ++i) vt[i].clear();
        int val;
        for(int i = n;i >= 1;--i)
        {
            b[i] = i;
            for(int j = 0;j < (int)factor[a[i]].size();++j)
            {
                val = factor[a[i]][j];
                for(int k = 0;k < (int)vt[val].size();++k)
                {
                    b[vt[val][k]] = i;
                }
                vt[val].clear();
            }
            vt[a[i]].push_back(i);
        }
        for(int i = 1;i <= maxv ; ++i) vt[i].clear();
        for(int i = 1;i <= n;++i)
        {
            c[i] = i;
            for(int j = 0;j < (int)factor[a[i]].size();++j)
            {
                val = factor[a[i]][j];
                for(int k = 0;k < (int)vt[val].size();++k)
                {
                    c[vt[val][k]] = i;
                }
                vt[val].clear();
            }
            vt[a[i]].push_back(i);
        }
        ll ans = 0;
        for(int i = 1;i <= n;++i)
            ans += (ll)a[b[i]]*a[c[i]];
        printf("%I64d\n",ans);
    }
    return 0;
}