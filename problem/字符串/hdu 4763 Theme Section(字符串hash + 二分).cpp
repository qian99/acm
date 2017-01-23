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
typedef unsigned long long ull;
const int maxn = 1000000 + 10;
const int mx = 233;
ull H[maxn],X[maxn];
char str[maxn];
int S[maxn],n;
inline ull getval(int x,int len)
{
    return H[x] - H[x + len]*X[len];
}
int lcp(int x,int y)
{
    int L = 0,R = n - y + 1,m;
    while(R - L > 1)
    {
        m = (L + R)>>1;
        if(getval(x,m) == getval(y,m))
            L = m;
        else
            R = m;
    }
    return L;
}
inline bool check(int s,int len)
{
    return s + len -1 < n - len;
}
int solve()
{
    n = strlen(str);
    H[n] = 0;
    for(int i = n - 1;i >= 0;--i)
        H[i] = H[i+1]*mx + str[i];
    int tot = 0;
    for(int i = n/3;i >= 1;--i)
        if(getval(0,i) == getval(n-i,i))
            S[tot++] = i;
    reverse(S,S + tot);
    if(tot == 0) return 0;
    int len,ans = 0,L,R,m;
    for(int i = 1;i < n-1;++i)
    {
        len = lcp(0,i);
        len = min(i,len);
        L = 0,R = tot;
        if(!check(i,min(S[0],len))) continue;
        while(R - L > 1)
        {
            m = (L+R)>>1;
            if(S[m] <= len && check(i,S[m]))
                L = m;
            else
                R = m;
        }
        ans = max(ans,S[L]);
    }
    return ans;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    X[0] = 1;
    for(int i = 1;i < maxn;++i)
        X[i] = X[i-1]*mx;
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%s",str);
        int ans = solve();
        printf("%d\n",ans);
    }
    return 0;
}
