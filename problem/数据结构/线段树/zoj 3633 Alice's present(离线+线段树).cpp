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
const int maxn=500000+10;
int num[maxn],n,m;
map<int,int>mp;
vector<pair<int,int> >q[maxn];
int ans[maxn],pre[maxn],last[maxn];
int sum[maxn<<2];
void PushUp(int rt)
{
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}
void build(int l,int r,int rt)
{
    sum[rt]=0;
    if(l==r) return ;
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
}
int Query(int L,int R,int l,int r,int rt)
{
    if(l==r)
    {
        return sum[rt]==0?-1:l;
    }
    if(l>=L&&r<=R&&sum[rt]==0)
        return -1;
    int m=(l+r)>>1;
    int res;
    if(m<R)
    {
        res=Query(L,R,m+1,r,rt<<1|1);
        if(res!=-1) return res;
    }
    if(m>=L) res=Query(L,R,l,m,rt<<1);
    return res;
}
void Update(int p,int l,int r,int rt,int v)
{
    if(l==r)
    {
        sum[rt]=v;
        return ;
    }
    int m=(l+r)>>1;
    if(m>=p) Update(p,l,m,rt<<1,v);
    else Update(p,m+1,r,rt<<1|1,v);
    PushUp(rt);
}
void solve()
{
    memset(pre,0xff,sizeof(pre));
    memset(last,0xff,sizeof(last));
    build(1,n,1);
    pair<int,int>tmp;
    for(int i=1;i<=n;++i)
    {
        int val=mp[num[i]];
        if(pre[val]!=-1)
        {
            if(last[val]!=-1) Update(last[val],1,n,1,0);
            Update(pre[val],1,n,1,1);
            last[val]=pre[val];
        }
        pre[val]=i;
        int size=q[i].size();
        for(int j=0;j<size;++j)
        {
            tmp=q[i][j];
            ans[tmp.second]=Query(tmp.first,i,1,n,1);
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d",&n))
    {
        mp.clear();
        int cnt=0;
        for(int i=1;i<=n;++i)
        {
            q[i].clear();
            scanf("%d",&num[i]);
            if(!mp[num[i]]) mp[num[i]]=++cnt;
        }
        scanf("%d",&m);
        int L,R;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d",&L,&R);
            q[R].push_back(make_pair(L,i));
        }
        solve();
        for(int i=0;i<m;++i)
        {
            if(ans[i]==-1)
                printf("OK\n");
            else
                printf("%d\n",num[ans[i]]);
        }
        printf("\n");
    }
    return 0;
}
