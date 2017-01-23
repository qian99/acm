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
const int maxn = 100 + 10;
char str[maxn];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    cin>>str;
    int n = strlen(str);
    int nb,ns,nc;
    int pb,ps,pc;
    int bb = 0,ss = 0,cc = 0;
    ll r;
    cin>>nb>>ns>>nc;
    cin>>pb>>ps>>pc;
    cin>>r;
    ll ans = 0;
    for(int i = 0;i < n;++i)
        if(str[i] == 'B') bb++;
        else if(str[i] == 'S') ss++;
        else cc++;
    if(bb==0) nb = 0;
    if(ss==0) ns = 0;
    if(cc==0) nc = 0;
    while(nb || ns || nc)
    {
        int b = min(bb,nb);
        int s = min(ss,ns);
        int c = min(cc,nc);
        int tmp = (bb-b)*pb + (ss-s)*ps + (cc-c)*pc;
        if(tmp <= r)
        {
            ans++;
            r -= tmp;
            nb -= b;
            ns -= s;
            nc -= c;
        }
        else break;
    }
    int cost = bb*pb + ss*ps + cc*pc;
    ans += r/cost;
    printf("%I64d\n",ans);
    return 0;
}