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
const int maxn=100000*3+10;
int num[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,k;
    while(~scanf("%d%d",&n,&k))
    {
        for(int i=0;i<n;++i)
         scanf("%d",&num[i]);
        sort(num,num+n);
        int ans=num[0];
        int j;
        while(true)
        {
            for(j=0;j<n;++j)
            {
                if(num[j]%ans>k)
                {
                    ans=num[j]/(num[j]/ans+1);
                    break;
                }
            }
            if(j==n) break;
        }
        printf("%d\n",ans);
    }
    return 0;
}
