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
const int maxn = 100000+10;
const int Size = 333;
int a[maxn],b[maxn],id[maxn],pos[maxn],c[maxn];
int d,n,x;
int getnext()
{
    x = (x*37LL + 10007LL)%1000000007;
    return x;
}
void Init()
{
    for(int i = 0;i < n ;++i)
        a[i] = i + 1;
    for(int i = 0;i <n ;++i)
        swap(a[i],a[getnext() % (i + 1)]);
    for(int i = 0; i < n; ++i)
    {
        if (i < d) b[i] = 1;
        else b[i] = 0;
    }
    for(int i = 0; i < n; i++)
        swap(b[i], b[getnext() % (i + 1)]);
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    scanf("%d%d%d",&n,&d,&x);
    Init();
    for(int i = 0;i < n;++i)
        id[a[i]] = i;
    int tot = 0;
    for(int i = 0;i < n;++i)
        if(b[i]) pos[tot++] = i;
    for(int i = 0;i < n;++i)
    {
        bool flag = false;
        for(int j = 0;j < Size;++j)
        {
            if(n - j < 1) break;
            if(id[n-j] <= i && b[i-id[n-j]])
            {
                c[i] = n - j;
                flag = true;
                break;
            }
        }
        if(!flag)
        {
            c[i] = 0;
            for(int j = 0;j < tot&&pos[j] <= i;++j)
                c[i] = max(c[i],a[i - pos[j]]);
        }
    }
    for(int i = 0;i < n;++i)
        printf("%d\n",c[i]);
    return 0;
}
