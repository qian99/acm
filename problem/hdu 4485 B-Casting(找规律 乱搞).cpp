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
const int maxn = 10000000 + 10;
char str[maxn];
//short p[maxn];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t,tcase;
    scanf("%d",&t);
    while(t--)
    {
        int B,mod;
        scanf("%d%d%s",&tcase,&B,str);
        int n = strlen(str);
        reverse(str,str + n);
        mod = B - 1;
//        p[0] = 1;
//        for(int i = 1;i < n;++i)
//            p[i] = p[i-1]*B%mod;
//        int ans = 0;
//        for(int i = 0;i < n;++i)
//            ans = (ans + p[i]*(str[i] - '0'))%mod;
        int res = 0;
        for(int i = 0;i < n;++i)
            res += str[i] - '0';
        printf("%d %d\n",tcase,res%mod);
    }
    return 0;
}
