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
const int maxn=100000+10;
int minv[maxn<<2],addv[maxn<<2],pos[maxn<<2];
int c[maxn],res[maxn<<1];
int n;
inline void PushUp(int rt)
{
    if(minv[rt<<1]==minv[rt<<1|1])
      pos[rt]=min(pos[rt<<1],pos[rt<<1|1]);
    else if(minv[rt<<1]<minv[rt<<1|1])
      pos[rt]=pos[rt<<1];
    else pos[rt]=pos[rt<<1|1];
    minv[rt]=min(minv[rt<<1],minv[rt<<1|1]);
}
void PushDown(int l,int r,int rt)
{
    if(addv[rt]!=0)
    {
        int ls=rt<<1,rs=rt<<1|1;
        addv[ls]+=addv[rt];
        addv[rs]+=addv[rt];
        minv[ls]=minv[ls]+addv[rt];
        minv[rs]=minv[rs]+addv[rt];
        addv[rt]=0;
    }
}
void build(int l,int r,int rt)
{
    addv[rt]=0;
    if(l==r)
    {
        minv[rt]=c[l];
        pos[rt]=l;
        return ;
    }
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
    PushUp(rt);
}
void Update(int L,int R,int l,int r,int rt,int v)
{
    if(l>=L&&r<=R)
    {
        addv[rt]+=v;
        minv[rt]+=v;
        return ;
    }
    PushDown(l,r,rt);
    int m=(l+r)>>1;
    if(m>=L)
      Update(L,R,l,m,rt<<1,v);
    if(m<R)
      Update(L,R,m+1,r,rt<<1|1,v);
    PushUp(rt);
}
bool solve()
{
    build(1,n,1);
    int N=n*5,L,R;
    queue<int>a;
    queue<int>b;
    while(true)
    {
        if(minv[1]<0) return false;
        if(minv[1]>n) break;
        if(minv[1]==0)
        {
            a.push(pos[1]);
            b.push(-pos[1]);
            L=1;R=pos[1]-1;
            if(L<=R)
              Update(L,R,1,n,1,-1);
            Update(R+1,R+1,1,n,1,N);
        }
        else
        {
            if(b.empty()) return false;
            int tmp=b.front();b.pop();
            a.push(tmp);
            L=1-tmp;R=n;
            if(L<=R)
              Update(L,R,1,n,1,-1);
        }
    }
    int cnt=2*n;
    while(!a.empty())
    {
        res[--cnt]=a.front();
        a.pop();
    }
    while(!b.empty())
    {
        res[--cnt]=b.front();
        b.pop();
    }
    return true;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        for(int i=1;i<=n;++i)
            scanf("%d",&c[i]);
        if(solve())
        {
            for(int i=0;i<n*2;++i)
              printf("%d ",res[i]);
            printf("\n");
        }
        else printf("Impossible\n");
    }
    return 0;
}
