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
const int maxn = 55;
int p[maxn],last[maxn][2];
char str[maxn];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    p[0] = 1;
    for(int i = 1;i < 30;++i) p[i] = p[i - 1]<<1;
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        for(int i = 0;i < 30;++i)
            last[i][0] = 0,last[i][1] = 1;
        int x;
        for(int i = 0;i < n;++i)
        {
            scanf("%s",str);
            scanf("%d",&x);
            for(int j = 0;j < 30;++j)
            {
                if(str[0] == 'A')
                {
                    last[j][0] &= ((x>>j)&1);
                    last[j][1] &= ((x>>j)&1);
                }
                else if(str[0] == 'O')
                {
                    last[j][0] |= ((x>>j)&1);
                    last[j][1] |= ((x>>j)&1);
                }
                else
                {
                    last[j][0] ^= ((x>>j)&1);
                    last[j][1] ^= ((x>>j)&1);
                }
            }
        }
        for(int i = 0;i < 30;++i)
        {
            last[i][0] *= p[i];
            last[i][1] *= p[i];
        }
        m++;
        int ans = 0;
        for(int i = 0;i < 30;++i)
        {
            if(!((m>>i)&1)) continue;
            int tmp = 0;
            for(int j = i + 1;j < 30;++j)
                tmp += last[j][(m>>j)&1];
            tmp += last[i][0];
            for(int j = 0;j < i;++j)
                tmp += max(last[j][0],last[j][1]);
            ans = max(tmp,ans);
        }
        printf("%d\n",ans);
    }
    return 0;
}
