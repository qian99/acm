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
#define inf 2139062143
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=100000+10;
ll sum[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        ll tmp;
        sum[0]=0;
        for(int i=1;i<=n;++i)
        {
            scanf("%I64d",&tmp);
            sum[i]=(sum[i-1]+tmp)%m;
        }
        int len=n;
        bool find=false;
        while(!find&&len>0)
        {
            for(int i=1;i+len-1<=n;++i)
            {
                if((sum[i+len-1]-sum[i-1])%m==0)
                {
                    find=true;
                    break;
                }
            }
            if(find) break;
            len--;
        }
        printf("%d\n",len);
    }
    return 0;
}
