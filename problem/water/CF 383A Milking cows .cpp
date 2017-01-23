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
const int maxn=200000+10;
int a[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        ll sum=0;
        for(int i=0;i<n;++i)
            scanf("%d",&a[i]);
        ll cnt=0;
        for(int i=n-1;i>=0;i--)
        {
            if(a[i]==0) cnt++;
            else sum+=cnt;
        }
        printf("%I64d\n",sum);
    }
    return 0;
}
