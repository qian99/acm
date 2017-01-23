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
const int maxn=55;
int a[maxn],n;
bool check(double len)
{
    double last = -1e10;
    for(int i = 0;i < n;++i)
    {
        if(last == a[i]) continue;
        if(last > a[i]) return false;
        if(last + len <= a[i])
        {
            last = a[i];
        }
        else
            last = a[i] +len;
    }
    return true;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w ",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        for(int i = 0;i < n;++i)
            scanf("%d",&a[i]);
        sort(a,a+n);
        double L = 0,R =1e10,m;
        while((R-L)>1e-5)
        {
            m = (L + R)/2;
            if(check(m)) L = m;
            else R = m;
        }
        for(int i = 0;i < n-1;++i)
            for(int j = i;j< n-1;++j)
            {
                R = a[j] - a[i];
                if(check(R)) L=max(L,R);
            }
        printf("%.3lf\n",L);
    }
    return 0;
}