#include <iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=20;
set<ll>s;
int a[maxn];
int n,x,y,z;
void dfs(int i)
{
    if(i==n+1)
    {
        if(x&&x<=y&&y<=z&&x+y>z) s.insert(x<<16|y);
        return;
    }
    x+=a[i];dfs(i+1);x-=a[i];
    y+=a[i];dfs(i+1);y-=a[i];
    z+=a[i];dfs(i+1);z-=a[i];
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
          scanf("%d",&a[i]);
        x=y=z=0;
        s.clear();
        dfs(1);
        int ans=s.size();
        printf("%d\n",ans);
    }
    return 0;
}
