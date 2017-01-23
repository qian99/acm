#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<vector>
#include<bitset>
#include<set>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=500000+10;
int a[maxn],n,m;
inline bool f(int x,int y,int a)
{
    int p=a/x+(a%x!=0);
    return p<=y;
}
bool check(int mid)
{
    int x=m,L,R,d;
    for(int i=1;i<=n;++i)
    {
        L=1,R=x;
        if(x==0||!f(x,mid,a[i])) return false;
        while(L<R)
        {
            d=(L+R)>>1;
            if(f(d,mid,a[i])) R=d;
            else L=d+1;
        }
        x-=L;
        if(x<0) return false;
    }
    return true;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d",&n,&m))
    {
        if(n==-1&&m==-1) break;
        int L=1,R=1;
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
            if(R<a[i]) R=a[i];
        }
        while(L<R)
        {
            int mid=(L+R)>>1;
            if(check(mid)) R=mid;
            else L=mid+1;
        }
        printf("%d\n",L);
    }
    return 0;
}
