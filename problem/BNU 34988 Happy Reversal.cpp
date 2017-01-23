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
const int maxn=10000+10;
pair<ll,int> num[maxn],fnum[maxn];
char str[110];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    int n,k;
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        scanf("%d%d",&n,&k);
        ll v,tmp1,tmp2;
        for(int i=0;i<n;++i)
        {
            scanf("%s",str);
            tmp1=tmp2=0;
            for(ll j=0;j<k;++j)
            {
                v=str[j]-'0';
                tmp1|=(v<<(k-j-1));
                tmp2|=((v^1)<<(k-j-1));
            }
            num[i]=make_pair(tmp1,i);
            fnum[i]=make_pair(tmp2,i);
        }
        sort(num,num+n);
        sort(fnum,fnum+n);
        ll ans=num[n-1].first-num[0].first;
        ans=max(fnum[n-1].first-fnum[0].first,ans);
        if(n>1)
        {
            if(num[n-1].second==fnum[0].second)
                ans=max(ans,max(num[n-1].first-fnum[1].first,num[n-2].first-fnum[0].first));
            else ans=max(ans,num[n-1].first-fnum[0].first);
            if(fnum[n-1].second==num[0].second)
                ans=max(ans,max(fnum[n-1].first-num[1].first,fnum[n-2].first-num[0].first));
            else ans=max(ans,fnum[n-1].first-num[0].first);
        }
        printf("Case #%d: %lld\n",tcase,ans);
    }
    return 0;
}
