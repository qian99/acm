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
const int maxn=100+10;
int num[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        for(int i=0;i<=n;++i)
           scanf("%d",&num[i]);
        bool flag=true;
        for(int i=0;i<=n;++i)
        {
            for(int j=i+1;j<=n;++j)
            {
                if(num[i]==num[j])
                {
                    printf("%d\n",num[i]);
                    flag=false;
                    break;
                }
            }
            if(!flag) break;
        }
    }
    return 0;
}
