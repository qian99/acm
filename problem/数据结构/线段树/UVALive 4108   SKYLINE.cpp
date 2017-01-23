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
//typedef long long ll;
const int maxn=100000+10;
const int N=100000;
int hightv[maxn<<2],setv[maxn<<2];
bool flag[maxn<<2];
int sum;
void PushUp(int rt)
{
    int ls=rt<<1,rs=rt<<1|1;
    hightv[rt]=max(hightv[ls],hightv[rs]);
    flag[rt]=(hightv[ls]==hightv[rs])&&flag[ls]&&flag[rs];
}
void PushDown(int rt)
{
    if(setv[rt]>=0)
    {
        int ls=rt<<1,rs=rt<<1|1;
        if(setv[rt]>=hightv[ls])
        {
            hightv[ls]=setv[rt];
            flag[ls]=true;
        }
        if(setv[rt]>=hightv[rs])
        {
            hightv[rs]=setv[rt];
            flag[rs]=true;
        }
        setv[ls]=max(setv[ls],setv[rt]);
        setv[rs]=max(setv[rs],setv[rt]);
        setv[rt]=-1;
    }
}
void build(int l,int r,int rt)
{
    hightv[rt]=0;
    setv[rt]=-1;
    flag[rt]=true;
    if(l==r) return;
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
}
void Update(int v,int L,int R,int l,int r,int rt)
{
    if(l>=L&&r<=R&&hightv[rt]<=v)
    {
        sum+=(r-l+1);
        setv[rt]=hightv[rt]=v;
        flag[rt]=true;
        return;
    }
    if(l>=L&&r<=R&&hightv[rt]>v&&flag[rt])
    {
        return;
    }
    PushDown(rt);
    int m=(l+r)>>1;
    int ls=rt<<1,rs=rt<<1|1;
    if(m>=L)
      Update(v,L,R,l,m,ls);
    if(m<R)
      Update(v,L,R,m+1,r,rs);
    PushUp(rt);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,l,r,h;
    int t;
    while(cin>>t)
    {
        if(t==0) break;
        while(t--)
        {
            cin>>n;
            build(1,N,1);
            int res=0;
            for(int i=0;i<n;++i)
            {
                cin>>l>>r>>h;
                sum=0;
                Update(h,l,r-1,1,N,1);
                res+=sum;
            }
            cout<<res<<endl;
        }
    }
    return 0;
}
