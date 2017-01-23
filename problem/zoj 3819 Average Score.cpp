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
int a[maxn],b[maxn];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    //x < a && x > b
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n,m;
        scanf("%d%d",&n,&m);
        for(int i = 0;i < n - 1;++i)
            scanf("%d",&a[i]);
        for(int i = 0;i < m;++i)
            scanf("%d",&b[i]);
        int sum1 = 0,sum2 = 0;
        for(int i = 0;i < n - 1;++i)
            sum1 += a[i];
        for(int i = 0;i < m;++i)
            sum2 += b[i];
        int L,R;
        L = sum2/m;
        R = sum1/(n - 1);
        if(L*m <= sum2) L++;
        if(R*(n - 1) >= sum1) R--;
        printf("%d %d\n",L,R);
    }
    return 0;
}
