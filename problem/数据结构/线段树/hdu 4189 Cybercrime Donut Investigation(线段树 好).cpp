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
#include<bitset>
#include<set>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=200000+10;
const int MAX=inf*2;
int maxv[maxn<<2],minv[maxn<<2];
void PushUp(int rt)
{
    maxv[rt]=max(maxv[rt<<1],maxv[rt<<1|1]);
    minv[rt]=min(minv[rt<<1],minv[rt<<1|1]);
}
void build(int l,int r,int rt)
{
    maxv[rt]=-MAX;
    minv[rt]=MAX;
    if(l==r) return ;
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
    PushUp(rt);
}
void Update(int p,int l,int r,int rt,int v)
{
    if(l==r)
    {
        maxv[rt]=max(maxv[rt],v);
        minv[rt]=min(minv[rt],v);
        return ;
    }
    int m=(l+r)>>1;
    if(m>=p) Update(p,l,m,rt<<1,v);
    else Update(p,m+1,r,rt<<1|1,v);
    PushUp(rt);
}
int Query(int L,int R,int l,int r,int rt,int type)
{
    if(l>=L&&r<=R)
    {
        if(type) return minv[rt];
        return maxv[rt];
    }
    int m=(l+r)>>1;
    if(m>=R) return Query(L,R,l,m,rt<<1,type);
    else if(m<L) return Query(L,R,m+1,r,rt<<1|1,type);
    else if(type) return min(Query(L,R,l,m,rt<<1,type),Query(L,R,m+1,r,rt<<1|1,type));
    return max(Query(L,R,l,m,rt<<1,type),Query(L,R,m+1,r,rt<<1|1,type));
}
struct Node
{
    int x,y,type;
    Node(){}
    Node(int x,int y,int type):x(x),y(y),type(type){}
}node[maxn];
bool cmp1(Node a,Node b)
{
    return (a.x==b.x&&a.type<b.type)||(a.x<b.x);
}
bool cmp2(Node a,Node b)
{
    return (a.x==b.x&&a.type<b.type)||(a.x>b.x);
}
int ans[maxn],num[maxn];
map<int,int>mp;
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int tcase=0;
    int n,m;
    while(~scanf("%d",&n))
    {
        if(n==-1) break;
        if(tcase) printf("\n");
        tcase++;
        mp.clear();
        int x,y,tot=0,N=0,tmp;
        for(int i=1;i<=n;++i)
        {
            scanf("%d%d",&x,&y);
            num[N++]=y;
            node[tot++]=Node(x,y,-i);
        }
        scanf("%d",&m);
        for(int i=1;i<=m;++i) ans[i]=MAX;
        for(int i=1;i<=m;++i)
        {
            scanf("%d%d",&x,&y);
            num[N++]=y;
            node[tot++]=Node(x,y,i);
        }
        sort(num,num+N);
        N=unique(num,num+N)-num;
        for(int i=0;i<N;++i)
            mp[num[i]]=i+1;
        sort(node,node+tot,cmp1);
        ///qx>=xi,qy>=yi
        build(1,N,1);
        for(int i=0;i<tot;++i)
        {
            if(node[i].type<0)
                Update(mp[node[i].y],1,N,1,node[i].x+node[i].y);
            else
            {
                tmp=Query(1,mp[node[i].y],1,N,1,0);
                if(tmp==-MAX) continue;
                ans[node[i].type]=min((ll)ans[node[i].type],(ll)node[i].x+node[i].y-tmp);
            }
        }
        ///qx>=xi,qy<=yi
        build(1,N,1);
        for(int i=0;i<tot;++i)
        {
            if(node[i].type<0)
                Update(mp[node[i].y],1,N,1,node[i].y-node[i].x);
            else
            {
                tmp=Query(mp[node[i].y],N,1,N,1,1);
                if(tmp==MAX) continue;
                ans[node[i].type]=min((ll)ans[node[i].type],(ll)node[i].x-node[i].y+tmp);
            }
        }
        sort(node,node+tot,cmp2);
        ///qx<=xi,qy>=yi
        build(1,N,1);
        for(int i=0;i<tot;++i)
        {
            if(node[i].type<0)
                Update(mp[node[i].y],1,N,1,node[i].x-node[i].y);
            else
            {
                tmp=Query(1,mp[node[i].y],1,N,1,1);
                if(tmp==MAX) continue;
                ans[node[i].type]=min((ll)ans[node[i].type],(ll)node[i].y-node[i].x+tmp);
            }
        }
        ///qx<=xi,qy<=yi
        build(1,N,1);
        for(int i=0;i<tot;++i)
        {
            if(node[i].type<0)
                Update(mp[node[i].y],1,N,1,node[i].x+node[i].y);
            else
            {
                tmp=Query(mp[node[i].y],N,1,N,1,1);
                if(tmp==MAX) continue;
                ans[node[i].type]=min((ll)ans[node[i].type],(ll)tmp-node[i].y-node[i].x);
            }
        }
        for(int i=1;i<=m;++i)
            printf("%d\n",ans[i]);
    }
    return 0;
}
