#include<iostream>
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
const int maxn=1000+10;
int a[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,ans=inf,minv,d;
    scanf("%d",&n);
    for(int i=0;i<n;++i)
        scanf("%d",&a[i]);
    sort(a,a+n);
    for(int i=0;i<=30000;++i)
    {
        int mx=0,mn=0;
        int now=a[0]+i;
        for(int j=1;j<n;++j)
        {
            mx=max(mx,a[j]-now);
            mn=min(mn,a[j]-now);
            now+=i;
        }
        int tmp=(mx-mn+1)/2;
        if(tmp<ans)
        {
            ans=tmp;
            minv=a[0]+(mx-tmp);
            d=i;
        }
    }
    printf("%d\n",ans);
    printf("%d %d\n",minv,d);
    return 0;
}
