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
const int maxn = 100 + 10;
int cnt[10],num[111],m,n;
bool check(int zero)
{
    bool flag = false;
    for(int i = 1;i <= 9;i += 2)
        if(cnt[i]) flag = true;
    if(zero == 0 && flag)
    {
        flag = false;
        int x = 0;
        for(int i = 1;i <= 9;++i)
            if(cnt[i]) x += cnt[i];
        if(x > 1 || n == 1) flag = true;
    }
    return flag;
}
void solve(int first)
{
    for(int i = 9;i >= first;--i)
    {
        if(!cnt[i]) continue;
        cnt[i]--;
        if(check(1) || (m+1) == n)
        {
           num[m++] = i;
           solve(0);
           break;
        }
        cnt[i]++;
    }
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    while(~scanf("%d",&n))
    {
        int x;
        memset(cnt,0,sizeof(cnt));
        for(int i = 0;i < n;++i)
        {
            scanf("%d",&x);
            cnt[x]++;
        }
        if(!check(0))
        {
            puts("-1");
            continue;
        }
        m = 0;
        solve(1);
        for(int i = 0;i < m;++i)
            printf("%d",num[i]);
        puts("");
    }
    return 0;
}
