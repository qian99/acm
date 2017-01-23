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
const int maxn = 5000 + 10;
int primes[10] = {2,3,5,7,11,13,17,23};
int a[maxn*10];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n;
    scanf("%d",&n);
    int cnt = 0,pos = 0;
    while(cnt < n)
    {
        a[cnt++] = primes[pos];
        for(int i = 0;i < cnt;++i)
            if(primes[pos]*a[i] <= 2*n*n)
                a[cnt++] = primes[pos]*a[i];
        pos++;
    }
    for(int i = 1;i <= n;++i)
        printf("%d ",a[cnt - i]);
    puts("");
    return 0;
}
