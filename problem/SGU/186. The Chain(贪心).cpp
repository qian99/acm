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
const int maxn=100+10;
int num[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;++i)
     scanf("%d",&num[i]);
    sort(num,num+n);
    int ans=0;
    int rm=n-1;
    for(int i=0;i<n;++i)
    {
        if(num[i]>=rm-1)
        {
            ans+=rm-1;
            if(num[i]>rm-1) ans++;
            rm=0;
            break;
        }
        else
        {
            ans+=num[i];
            rm-=num[i];
            rm--;
        }
    }
    if(rm) ans+=rm;
    printf("%d\n",ans);
    return 0;
}
