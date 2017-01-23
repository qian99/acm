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
int cnt[30];
char str[maxn];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%s",str);
        int n = strlen(str);
        int K;
        scanf("%d",&K);
        int head = 0,c;
        ll ans = 1;
        memset(cnt,0,sizeof(cnt));
        cnt[str[0] - 'a']++;
        for(int i = 1;i < n;++i)
        {
            c = str[i] - 'a';
            cnt[c]++;
            while(cnt[c] > K)
            {
                cnt[str[head] - 'a']--;
                head++;
            }
            ans += i - head + 1;
        }
        printf("%I64d\n",ans);
    }
    return 0;
}
