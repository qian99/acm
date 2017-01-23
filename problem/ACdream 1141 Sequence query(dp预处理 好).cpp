#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<set>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=100000+10;
int num[maxn],lf[maxn],rn[maxn];
ll maxv[maxn],ans1[maxn];
pair<ll,int>ans2[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n,m;
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;++i)
            scanf("%d",&num[i]);
        num[0]=num[n+1]=-1;
        lf[0]=0;
        for(int i=1;i<=n;++i)
        {
            if(num[i]>num[i-1]) lf[i]=i-1;
            else
            {
                lf[i]=i-1;
                while(num[lf[i]]>=num[i]) lf[i]=lf[lf[i]];
            }
        }
        rn[n+1]=n+1;
        for(int i=n;i>=1;--i)
        {
            if(num[i]>num[i+1]) rn[i]=i+1;
            else
            {
                rn[i]=i+1;
                while(num[rn[i]]>=num[i]) rn[i]=rn[rn[i]];
            }
        }
        memset(maxv,0xff,sizeof(maxv));
        ll tmp,mpre;
        for(int i=n;i>=1;--i)
        {
            int len=rn[i]-lf[i]-1;
            maxv[len]=max(maxv[len],(ll)num[i]);
        }
        tmp=mpre=-1;
        int tot=0;
        for(int i=n;i>=1;--i)
        {
            mpre=max(mpre,maxv[i]);
            ans1[i]=max(tmp,mpre*i);
            if(mpre>0) ans2[tot++]=make_pair(mpre*i,i);
            tmp=ans1[i];
        }
        tmp=1;
        sort(ans2,ans2+tot);
        for(int i=1;i<tot;++i)
            if(ans2[i].first!=ans2[tmp-1].first)
                ans2[tmp++]=ans2[i];
        tot=tmp;
        for(int i=tot-2;i>=0;--i)
            ans2[i].second=min(ans2[i].second,ans2[i+1].second);
        int type;
        ll x;
        while(m--)
        {
            scanf("%d%lld",&type,&x);
            if(type==1)
            {
                if(x<1) x=1;
                if(x>n) printf("-1\n");
                else printf("%lld\n",ans1[x]);
            }
            else
            {
                if(ans2[tot-1].first<x) printf("-1\n");
                else
                {
                    int pos=lower_bound(ans2,ans2+tot,make_pair(x,-1))-ans2;
                    printf("%d\n",ans2[pos].second);
                }
            }
        }
    }
    return 0;
}
