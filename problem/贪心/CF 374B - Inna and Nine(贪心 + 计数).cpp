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
#include<assert.h>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 100000+10;
char str[maxn];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    scanf("%s",str);
    int n = strlen(str);
    ll ans = 1;
    for(int i = 0;i < n-1;++i)
    {
        int j = i;
        while(str[j]+str[j+1] -'0'-'0' == 9) j++;
        if((j-i+1)&1) ans *= (j-i+1)/2 + 1;
        i = j;
    }
    printf("%I64d\n",ans);
    return 0;
}
