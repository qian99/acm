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
const int maxn = 200000 + 10;
int a[maxn],b[maxn],next[maxn];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i = 0;i < n;++i)
        scanf("%d",&a[i]);
    for(int i = 0;i < m;++i)
        scanf("%d",&b[i]);
    if(n < m)
    {
        puts("0");
        return 0;
    }
    if(m == 1)
    {
        printf("%d\n",n);
        return 0;
    }
    for(int i = 0;i < n - 1;++i)
        a[i] = a[i + 1] - a[i];
    for(int i = 0;i < m - 1;++i)
        b[i] = b[i + 1] - b[i];
    n--;m--;
    next[0] = next[1] = 0;
    for(int i = 1;i < n;++i)
    {
        int j = next[i];
        while(j && b[i] != b[j]) j = next[j];
        next[i+1] = (b[i] == b[j])?j + 1:0;
    }
    int fail = 0,cnt = 0;
    for(int i = 0;i < n;++i)
    {
        while(fail && b[fail] != a[i]) fail = next[fail];
        if(b[fail] == a[i]) fail++;
        if(fail == m)
        {
            cnt++;
            fail = next[fail];
        }
    }
    printf("%d\n",cnt);
    return 0;
}
