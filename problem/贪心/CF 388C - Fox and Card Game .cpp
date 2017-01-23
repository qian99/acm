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
int pile[maxn][maxn],size[maxn],num[maxn],cnt,n;
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d",&n))
    {
        int sum=0;
        for(int i=0;i<n;++i)
        {
            scanf("%d",&size[i]);
            for(int j=0;j<size[i];++j)
            {
                scanf("%d",&pile[i][j]);
                sum+=pile[i][j];
            }
        }
        int ans=0,cnt=0,m;
        for(int i=0;i<n;++i)
        {
            m=size[i]/2;
            if(size[i]&1) num[cnt++]=pile[i][m];
            for(int j=0;j<m;++j)
                ans+=pile[i][j];
        }
        sort(num,num+cnt);
        for(int i=cnt-1;i>=0;i-=2)
            ans+=num[i];
        printf("%d %d\n",ans,sum-ans);
    }
    return 0;
}
