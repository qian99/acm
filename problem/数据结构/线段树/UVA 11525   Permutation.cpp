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
int sum[maxn<<2],S[maxn],res[maxn];
void PushUp(int rt)
{
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}
void build(int l,int r,int rt)
{
    if(l==r)
    {
        sum[rt]=1;
        return;
    }
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
    PushUp(rt);
}
int Update(int v,int l,int r,int rt)
{
    if(l==r)
    {
        sum[rt]=0;
        return l;
    }
    int m=(l+r)>>1;
    int ls=rt<<1,rs=rt<<1|1;
    int res;
    if(sum[ls]>v)
       res=Update(v,l,m,ls);
    else
       res=Update(v-sum[ls],m+1,r,rs);
    PushUp(rt);
    return res;
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
        for(int i=0;i<k;++i)
           cin>>S[i];
        build(1,k,1);
        for(int i=0;i<k;++i)
        {
            res[i]=Update(S[i],1,k,1);
        }
        for(int i=0;i<k-1;++i)
           cout<<res[i]<<" ";
        cout<<res[k-1]<<endl;
    }
    return 0;
}
