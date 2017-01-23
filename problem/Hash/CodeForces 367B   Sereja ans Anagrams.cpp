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
const int maxn=200000+10;
int a[maxn],ans[maxn],b[maxn],cnt;
int n,m,p;
map<int,int>mp,pk;
void solve(int s)
{
    if(s+(ll)p*(m-1)>n) return ;
    pk.clear();
    int t=0,tmp,tmp2;
    for(int i=s;i<=s+(ll)p*(m-1);i+=p)
    {
        pk[a[i]]++;
        if(mp.find(a[i])!=mp.end()) tmp=mp[a[i]];
        else tmp=0;
        if(pk[a[i]]==tmp) t++;
        else if(pk[a[i]]==tmp+1)
            t--;
    }
    if(t==mp.size()) ans[cnt++]=s;
    for(ll i=s+(ll)p*m;i<=n;i+=p)
    {
        int k=i-(ll)m*p;
        if(a[k]!=a[i])
        {
            pk[a[k]]--;pk[a[i]]++;
            if(mp.find(a[k])!=mp.end()) tmp=mp[a[k]];
            else tmp=0;
            if(mp.find(a[i])!=mp.end()) tmp2=mp[a[i]];
            else tmp2=0;
            if(pk[a[k]]+1==tmp) t--;
            else if(pk[a[k]]==tmp) t++;
            if(pk[a[i]]==tmp2) t++;
            else if(pk[a[i]]==tmp2+1) t--;
        }
        if(t==mp.size())
            ans[cnt++]=k+p;
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%d%d%d",&n,&m,&p);
    for(int i=1;i<=n;++i)
        scanf("%d",&a[i]);
    for(int i=0;i<m;++i)
    {
        scanf("%d",&b[i]);
        if(mp[b[i]]) mp[b[i]]++;
        else mp[b[i]]=1;
    }
    cnt=0;
    for(int i=1;i<=min(p,n);++i)
        solve(i);
    sort(ans,ans+cnt);
    printf("%d\n",cnt);
    for(int i=0;i<cnt;++i)
    {
        if(i) printf(" ");
        printf("%d",ans[i]);
    }
    return 0;
}
