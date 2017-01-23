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
const int maxn=20000+10;
int s[maxn],sa[maxn],t[maxn],t2[maxn],c[maxn],n;
int rank[maxn],height[maxn];
void build_sa(int n,int m)
{
    int i,*x=t,*y=t2;
    for(i=0;i<m;++i) c[i]=0;
    for(i=0;i<n;++i) c[x[i]=s[i]]++;
    for(i=1;i<m;++i) c[i]+=c[i-1];
    for(i=n-1;i>=0;--i) sa[--c[x[i]]]=i;
    for(int k=1;k<=n;k<<=1)
    {
        int p=0;
        for(i=n-k;i<n;++i) y[p++]=i;
        for(i=0;i<n;++i) if(sa[i]>=k) y[p++]=sa[i]-k;
        for(i=0;i<m;++i) c[i]=0;
        for(i=0;i<n;++i) c[x[y[i]]]++;
        for(i=1;i<m;++i) c[i]+=c[i-1];
        for(i=n-1;i>=0;--i) sa[--c[x[y[i]]]]=y[i];
        swap(x,y);
        p=1,x[sa[0]]=0;
        for(i=1;i<n;++i)
            x[sa[i]]=(y[sa[i-1]]==y[sa[i]]&&y[sa[i-1]+k]==y[sa[i]+k])?p-1:p++;
        if(p>=n) break;
        m=p;
    }
}
void getHeight(int n)
{
    int i,j,k=0;
    for(i=0;i<=n;++i) rank[sa[i]]=i;
    for(i=0;i<n;++i)
    {
        if(k) k--;
        j=sa[rank[i]-1];
        while(s[i+k]==s[j+k]) k++;
        height[rank[i]]=k;
    }
}
bool test(int lim)
{
    int i=0,maxv,minv;
    maxv=minv=sa[1];
    for(i=2;i<n;++i)
    {
        if(height[i]>=lim)
        {
            maxv=max(maxv,sa[i]);
            minv=min(minv,sa[i]);
            if(maxv-minv>lim) return true;
        }
        else
            maxv=minv=sa[i];
    }
    return false;
}
int solve()
{
    int l=4,r=n,m,ans=0;
    while(r>=l)
    {
        m=(l+r)/2;
        if(test(m))
        {
            ans=m;
            l=m+1;
        }
        else
            r=m-1;
    }
    return ans<4?0:ans+1;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        memset(height,0,sizeof(height));
        for(int i=0;i<n;++i)
            scanf("%d",&s[i]);
        for(int i=0;i<n-1;++i)
            s[i]=s[i+1]-s[i]+90;
        s[n-1]=0;
        build_sa(n,200);
        getHeight(n-1);
        printf("%d\n",solve());
    }
    return 0;
}
