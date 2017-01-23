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
typedef unsigned long long ull;
const int maxn = 100000 + 10;
const int mx = 233;
ull H1[maxn],H2[maxn],p[maxn];
char s1[maxn],s2[maxn],convert[30],cx[30];
ull gethash(ull * H,int x,int len)
{
    return H[x] - H[x + len]*p[len];
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    p[0] = 1;
    for(int i = 1;i < maxn; ++i) p[i] = p[i-1]*mx;
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%s",convert);
        for(int i = 0;i < 26;++i)
            cx[convert[i] - 'a'] = i + 'a';
        scanf("%s",s1);
        int n = strlen(s1);
        for(int i = 0;i < n;++i)
            s2[i] = convert[s1[i] - 'a'];
        H1[n] = H2[n] = 0;
        for(int i = n - 1;i >= 0;--i)
        {
            H1[i] = H1[i+1]*mx + s1[i];
            H2[i] = H2[i+1]*mx + s2[i];
        }
        int pos = -1;
        ull x,y;
        for(int i = (n + 1)/2;i < n;++i)
        {
            x = gethash(H1,0,n - i);
            y = gethash(H2,i,n - i);
            if(x == y)
            {
                pos = i;
                break;
            }
        }
        if(pos == -1) pos = n;
        for(int i = 0;i < pos;++i)
            putchar(s1[i]);
        for(int i = 0;i < pos;++i)
            putchar(cx[s1[i] - 'a']);
        puts("");
    }
    return 0;
}
