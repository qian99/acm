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
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        ll sum=0;
        int tmp;
        for(int i=0;i<n;++i)
        {
            scanf("%d",&tmp);
            sum+=tmp*tmp;
        }
        printf("%I64d\n",sum);
    }
    return 0;
}
