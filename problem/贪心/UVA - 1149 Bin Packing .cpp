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
#include<bitset>
#include<set>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=100000+10;
int num[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n,W;
    scanf("%d",&t);
    for(int tcase=0;tcase<t;++tcase)
    {
        if(tcase) printf("\n");
        scanf("%d%d",&n,&W);
        for(int i=1;i<=n;++i)
            scanf("%d",&num[i]);
        sort(num+1,num+n+1);
        int ans=0,lp=n;
        for(int i=1;i<=lp;++i)
        {
            ans++;
            while(i<lp&&num[i]+num[lp]>W) lp--,ans++;
            if(i!=lp&&num[i]+num[lp]<=W) lp--;
        }
        printf("%d\n",ans);
    }
    return 0;
}
