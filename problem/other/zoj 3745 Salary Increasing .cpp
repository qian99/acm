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
const int maxn=100000+10;
int num[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,q;
    while(~scanf("%d%d",&n,&q))
    {
        int tmp;
        ll sum=0;
        memset(num,0,sizeof(num));
        for(int i=0;i<n;++i)
        {
            scanf("%d",&tmp);
            num[tmp]++;
            sum+=tmp;
        }
        int l,r,c;
        while(q--)
        {
            scanf("%d%d%d",&l,&r,&c);
            //if(l>r) swap(l,r);
            for(int i=r;i>=l;--i)
            {
                sum+=(ll)c*num[i];
                if(i+c<maxn) num[i+c]+=num[i];
                num[i]=0;
            }
        }
        printf("%lld\n",sum);
    }
    return 0;
}

