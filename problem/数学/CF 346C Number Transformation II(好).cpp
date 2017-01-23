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
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=100000+10;
int x[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,a,b,ans=0;
    scanf("%d",&n);
    for(int i=0;i<n;++i)
        scanf("%d",&x[i]);
    sort(x,x+n);
    n=unique(x,x+n)-x;
    scanf("%d%d",&a,&b);
    while(a>b)
    {
        int maxv=1;
        for(int i=0;i<n;++i)
            if(a-a%x[i]>=b) maxv=max(maxv,a%x[i]);
        a-=maxv;
        while(n-1&&(a-a%x[n-1]<b)) n--;
        ans++;
    }
    printf("%d\n",ans);
    return 0;
}
