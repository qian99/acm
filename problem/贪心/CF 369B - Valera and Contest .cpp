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
const int maxn = 1000 + 10;
int ans[maxn];
bool build(int l,int r,int base,int top,int sum)
{
    if(l > r) return true;
    int len = r - l + 1;
    int tmp = len*base;
    if(tmp > sum) return false;
    if(tmp == sum)
    {
        for(int i = l;i <= r;++i)
            ans[i] = base;
        return true;
    }
    if(base == top) return false;
    if(tmp + len >= sum)
    {
        for(int i = l;i <= r;++i)
        {
            sum -= base;
            ans[i] = base;
        }
        for(int i = l;i <= r;++i)
        {
            if(!sum) break;
            sum--;
            ans[i]++;
        }
        return true;
    }
    return false;
}
int main()
{
//    freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,k,l,r,sall,sk;
    scanf("%d%d%d%d%d%d",&n,&k,&l,&r,&sall,&sk);
    int lim;
    for(int i = r;i >= l;--i)
    {
        if(build(1,k,i,r,sk))
        {
            lim = i;
            break;
        }
    }
    for(int i = lim;i >= l;--i)
    {
        if(build(k+1,n,i,lim,sall-sk))
        {
            break;
        }
    }
    for(int i = 1;i <= n;++i)
        printf("%d ",ans[i]);
    puts("");
    return 0;
}