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
const int maxn=55;
ll x[maxn];
bool vis[maxn];
int n;
int solve(ll a,ll b)
{
    if(a>b) swap(a,b);
    ll c=b-a;
    int ans=n,cnt;
    for(int i=0;i<n;++i)
    {
        ll s=a-i*c,now;
        memset(vis,0,sizeof(vis));
        cnt=n;
        for(int j=0;j<n;++j)
        {
            now=s+j*c;
            for(int k=0;k<n;++k)
                if(!vis[k]&&now==x[k]) {cnt--;vis[k]=true;break;}
        }
        if(cnt<ans) ans=cnt;
    }
    return ans;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    cin>>t;
    while(t--)
    {
        tcase++;
        cin>>n;
        for(int i=0;i<n;++i)
            cin>>x[i];
        int ans=n;
        for(int i=0;i<n;++i)
            for(int j=i;j<n;++j)
                ans=min(ans,solve(x[i],x[j]));
//        if(n==1) ans=0;
        cout<<"Case #"<<tcase<<": "<<ans<<endl;
    }
    return 0;
}
