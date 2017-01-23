#include <iostream>
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
const int maxn=500000+10;
int num[maxn],n;
bool test(int mid)
{
    if(mid==0) return true;
    int s=n-mid-1,t=n-1;
    while(s>=0&&t>n-mid-1)
    {
        while(num[s]*2>num[t]&&s>=0) s--;
        if(s<0) break;
        t--;s--;
    }
    return t<=n-mid-1;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%d",&n);
    for(int i=0;i<n;++i)
        scanf("%d",&num[i]);
    sort(num,num+n);
    int l=0,r=n,ans=0;
    while(l<r)
    {
        int m=(l+r)>>1;
        if(test(m))
        {
            ans=m;
            l=m+1;
        }
        else
            r=m;
    }
    printf("%d\n",n-ans);
    return 0;
}
