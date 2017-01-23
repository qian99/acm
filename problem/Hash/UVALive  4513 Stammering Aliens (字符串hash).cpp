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
typedef unsigned long long Ull;
const int maxn=400000+10;
const int x=233;
Ull hash[maxn],xp[maxn],val[maxn];
int rank[maxn];
char str[maxn];
int m,n,maxpos;
bool cmp(const int &a,const int &b)
{
    return (val[a]<val[b])||(val[a]==val[b]&&a<b);
}
bool check(int len)
{
    for(int i=0;i<n-len+1;++i)
    {
        val[i]=hash[i]-hash[i+len]*xp[len];
        rank[i]=i;
    }
    sort(rank,rank+n-len+1,cmp);
    int now=0;
    maxpos=-1;
    Ull last=val[rank[0]];
    for(int i=0;i<n-len+1;++i)
    {
        if(val[rank[i]]==last) now++;
        else {now=1;last=val[rank[i]];}
        if(now>=m) maxpos=max(maxpos,rank[i]);
    }
    return maxpos>=0;
}
int solve()
{
    int L=1,R=n+1;
    if(!check(1)) return -1;
    while(R-L>1)
    {
        int mid=(L+R)>>1;
        if(check(mid)) L=mid;
        else R=mid;
    }
    check(L);
    return L;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d",&m))
    {
        if(m==0) break;
        scanf("%s",str);
        n=strlen(str);
        hash[n]=0;
        for(int i=n-1;i>=0;--i)
            hash[i]=hash[i+1]*x+(str[i]-'a');
        xp[0]=1;
        for(int i=1;i<=n;++i) xp[i]=xp[i-1]*x;
        int ans=solve();
        if(ans==-1) printf("none\n");
        else printf("%d %d\n",ans,maxpos);
    }
    return 0;
}
