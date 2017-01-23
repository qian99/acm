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
typedef unsigned long long Ull;
const int mx = 233;
const int maxn = 100000+10;
char str[maxn];
Ull H[maxn],x[maxn];
map<Ull,int>mp;
inline Ull getval(int s,int len)
{
    return H[s] - H[s+len]*x[len];
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    x[0] = 1;
    for(int i = 1;i < maxn;++i) x[i] = x[i-1]*mx;
    int M,L;
    while(~scanf("%d%d",&M,&L))
    {
        scanf("%s",str);
        int n = strlen(str);
        H[n] = 0;
        for(int i = n - 1;i >= 0;--i)
            H[i] = H[i+1]*mx + str[i] - 'a';
//        getval(9,3);
        Ull tval;
        int v,ans = 0;
        for(int i = 0;i < L;++i)
        {
            if(i + M*L > n) break;
            mp.clear();
            int s = i, t = i + (M-1)*L;
            int cnt = 0;
            for(int j = s;j <= t; j += L)
            {
                tval = getval(j,L);
                if(mp.find(tval) == mp.end())
                    mp[tval] = 1;
                else
                {
                    v = mp[tval];
                    if(v == 1) cnt++;
                    mp[tval]++;
                }
            }
            if(cnt == 0) ans++;
            while(t + 2*L <= n)
            {
                tval = getval(s,L);
                v = mp[tval];
                if(v > 2) mp[tval]--;
                else if(v == 2) cnt--,mp[tval]--;
                else mp.erase(tval);
                s += L;
                tval = getval(t+L,L);
                if(mp.find(tval) == mp.end())
                    mp[tval] = 1;
                else
                {
                    v = mp[tval];
                    if(v == 1) cnt++;
                    mp[tval]++;
                }
                t += L;
                if(cnt == 0) ans ++;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
