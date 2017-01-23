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
const int maxn = 1000 + 10;
char str[maxn];
int sum[maxn];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t,tcase = 0;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%s",str);
        memset(sum,0,sizeof(sum));
        int n = strlen(str);
        sum[0] = 1<<(str[0] - 'a');
        for(int i = 1;i < n;++i)
            sum[i] = sum[i-1]^(1<<(str[i] - 'a'));
        int val,ans = 0;
        for(int i = 0;i < n;++i)
            for(int j = i;j < n;++j)
            {
                if(i == 0) val = sum[j];
                else val = sum[j]^sum[i - 1];
                if(val == 0)
                    ans++;
                else if((j - i + 1) & 1)
                {
                    int cnt = 0;
                    while(val)
                    {
                        cnt++;
                        val &= (val - 1);
                        if(cnt > 1) break;
                    }
                    if(cnt == 1)
                        ans++;
                }
            }
        printf("Case %d: %d\n",++tcase,ans);
    }
    return 0;
}

