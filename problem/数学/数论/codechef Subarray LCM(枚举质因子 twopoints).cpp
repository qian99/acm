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
#include<bitset>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 100000 + 10;
const int maxm = 1000000 + 10;
vector<int>factor[maxm];
bool flag[maxm];
void Init()
{
    for(int i = 2;i < maxm;++i)
    {
        if(factor[i].size() > 1) continue;
        for(int j = i;j < maxm;j += i)
            factor[j].push_back(i);
    }
}
int a[maxn];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    Init();
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n;
        scanf("%d",&n);
        for(int i = 1;i <= n;++i)
            scanf("%d",&a[i]);
        int last = 1;
        memset(flag,0,sizeof(flag));
        for(int j = 0;j < (int)factor[a[1]].size();++j)
            flag[factor[a[1]][j]] = 1;
        int ans = 1;
        for(int i = 2;i <= n;++i)
        {
            int x = a[i],y;
            for(int j = 0;j < (int)factor[x].size();++j)
            {
                y = factor[x][j];
                while(flag[y])
                {
                    for(int k = 0;k < (int)factor[a[last]].size();++k)
                    {
                        flag[factor[a[last]][k]] = 0;
                    }
                    last++;
                }
                flag[y] = 1;
            }
            ans = max(ans,i - last + 1);
        }
        if(ans == 1) ans = -1;
        printf("%d\n",ans);
    }
    return 0;
}
