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
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    ll sum1,sum2;
    int n,tmp,k;
    while(~scanf("%d%d",&n,&k))
    {
        sum1=sum2=0;
        for(int i=0;i<n;++i)
        {
            scanf("%d",&tmp);
            if(tmp>=k) sum1+=tmp-k;
            else sum2+=k-tmp;
        }
        printf("%I64d %I64d\n",sum1,sum2);
    }
    return 0;
}
