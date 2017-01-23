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
struct Node
{
    int S,T;
};
Node flower[maxn];
int num[maxn<<2],querys[maxn],N;
int sum[maxn<<4],addv[maxn<<4];
inline void PushUp(int rt)
{
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}
void PushDown(int l,int r,int rt)
{
    if(addv[rt])
    {
        int m=(l+r)>>1;
        addv[rt<<1]+=addv[rt];
        addv[rt<<1|1]+=addv[rt];
        sum[rt<<1]+=(m-l+1)*addv[rt];
        sum[rt<<1|1]+=(r-m)*addv[rt];
        addv[rt]=0;
    }
}
void build(int l,int r,int rt)
{
    sum[rt]=addv[rt]=0;
    if(l==r) return ;
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
}
void Update(int L,int R,int l,int r,int rt)
{
    if(l>=L&&r<=R)
    {
        addv[rt]++;
        sum[rt]+=(r-l+1);
        return ;
    }
    PushDown(l,r,rt);
    int m=(l+r)>>1;
    if(m>=L)
     Update(L,R,l,m,rt<<1);
    if(m<R)
     Update(L,R,m+1,r,rt<<1|1);
    PushUp(rt);
}
int Query(int p,int l,int r,int rt)
{
    if(l==r)
    {
        return sum[rt];
    }
    PushDown(l,r,rt);
    int m=(l+r)>>1;
    if(m>=p)
     return Query(p,l,m,rt<<1);
    return Query(p,m+1,r,rt<<1|1);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0,n,m;
    map<int,int>mp;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        tcase++;
        mp.clear();
        int cnt=1,zcnt;
        for(int i=0;i<n;++i)
        {
            scanf("%d%d",&flower[i].S,&flower[i].T);
            num[cnt++]=flower[i].S;
            num[cnt++]=flower[i].T;
        }
        for(int i=0;i<m;++i)
        {
            scanf("%d",&querys[i]);
            num[cnt++]=querys[i];
        }
        sort(num+1,num+cnt);
        zcnt=2;
        mp[num[1]]=1;
        for(int i=2;i<cnt;++i)
        {
            if(num[i]==num[i-1]) continue;
            mp[num[i]]=zcnt++;
        }
        N=zcnt-1;
        build(1,N,1);
        for(int i=0;i<n;++i)
         Update(mp[flower[i].S],mp[flower[i].T],1,N,1);
        printf("Case #%d:\n",tcase);
        for(int i=0;i<m;++i)
        {
            int ans=Query(mp[querys[i]],1,N,1);
            printf("%d\n",ans);
        }
    }
    return 0;
}
