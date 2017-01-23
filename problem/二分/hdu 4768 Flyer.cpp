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
const int maxn = 200000 + 10;
ll A[maxn],B[maxn],C[maxn],n;
ll check(int L,int R)
{
    ll sum = 0,k;
    int l,r;
    for(int i = 0;i < n;++i)
    {
        l = L; r = R;
        if(r > B[i]) r = B[i];
        if(l < A[i]) l = A[i];
        if(l > r) continue;
        k = (r - A[i])/C[i];
        if(A[i] + k*C[i] > r) k--;
        sum += k;
        k = (l - A[i])/C[i];
        if(A[i] + k*C[i] >= l) k--;
        sum -= k;
    }
    return sum;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    while(~scanf("%I64d",&n))
    {
        ll L = (1LL<<31) - 1,R = 0;
        for(int i = 0;i < n;++i)
        {
            scanf("%I64d%I64d%I64d",&A[i],&B[i],&C[i]);
            R = max(R,B[i]);
            L = min(L,A[i]);
        }
//        R = 100000;
        if(!(check(L,R) & 1))
        {
            puts("DC Qiang is unhappy.");
            continue;
        }
        while(L < R)
        {
            int m = (L + R)>>1;
            if(check(L,m) & 1)
                R = m;
            else
                L = m + 1;
        }
        printf("%I64d %I64d\n",L,check(L,L));
    }
    return 0;
}
