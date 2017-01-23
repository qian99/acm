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
int sum[maxn],N;
inline int lowbit(int x)
{
    return x&-x;
}
void add(int x)
{
    while(x<=N)
    {
        sum[x]++;
        x+=lowbit(x);
    }
}
int getv(int x)
{
    int res=0;
    while(x>0)
    {
        res+=sum[x];
        x-=lowbit(x);
    }
    return res;
}
struct Node
{
    int id,x,y;
    bool operator <(const Node & a) const
    {
        return (x==a.x&&id<a.id)||(x>a.x);
    }
}node[maxn];
int num[maxn],ans[maxn];
map<int,int>mp;
int Len(double x1,double y1,double x2,double y2)
{
    double tmp=(x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
    tmp=sqrt(tmp);
    return floor(tmp);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int x1,y1,x2,y2;
    int n,m,x,y;
    while(~scanf("%d%d%d%d",&x1,&y1,&x2,&y2))
    {
        mp.clear();
        N=0;
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%d%d",&x,&y);
            node[i].x=Len(x,y,x1,y1);
            node[i].y=Len(x,y,x2,y2);
            node[i].id=-i;
            num[N++]=node[i].y;
        }
        scanf("%d",&m);
        for(int i=1;i<=m;++i)
        {
            scanf("%d%d",&node[i+n].x,&node[i+n].y);
            node[i+n].id=i;
            num[N++]=node[i+n].y;
        }
        sort(num,num+N);
        N=unique(num,num+N)-num;
        for(int i=0;i<N;++i)
            mp[num[i]]=i+1;
        sort(node+1,node+n+m+1);
        memset(sum,0,sizeof(sum));
        for(int i=1;i<=n+m;++i)
        {
            int p=mp[node[i].y];
            if(node[i].id<0)
            {
                add(p);
            }
            else
            {
                ans[node[i].id]=getv(N)-getv(p-1);
            }
        }
        for(int i=1;i<=m;++i)
            printf("%d\n",ans[i]);
    }
    return 0;
}
