#include <iostream>
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
const int maxn=50000+10;
int sum[maxn],S[maxn],res[maxn];
int lowbit(int x)
{
    return x&-x;
}
void add(int x,int v,int n)
{
    while(x<=n)
    {
        sum[x]+=v;
        x+=lowbit(x);
    }
}
int su(int x)
{
    int ret=0;
    while(x>0)
    {
        ret+=sum[x];
        x-=lowbit(x);
    }
    return ret;
}
void Init(int k)
{
    memset(sum,0,sizeof(sum));
    for(int i=1;i<=k;++i)
      add(i,1,k);
    for(int i=0;i<k;++i)
      cin>>S[i];
}
int f(int v,int l,int r)
{
    int m,w;
    while(l<r)
    {
        m=(l+r)>>1;
        w=su(m);
        if(w>v)
        {
            r=m;
        }
        else
        {
            l=m+1;
        }
    }
    return l;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,k;
    cin>>t;
    while(t--)
    {
        cin>>k;
        Init(k);
        for(int i=0;i<k;++i)
        {
            res[i]=f(S[i],1,k);
            add(res[i],-1,k);
        }
        for(int i=0;i<k-1;++i)
           cout<<res[i]<<" ";
        cout<<res[k-1]<<endl;
    }
    return 0;
}
