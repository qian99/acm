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
const int maxn=500000+10;
vector<pair<int,int> >shot[maxn];
int maxv[maxn<<2],addv[maxn<<2];
inline void PushUp(int rt)
{
    maxv[rt]=max(maxv[rt<<1],maxv[rt<<1|1]);
}
inline void PushDown(int rt)
{
    if(addv[rt])
    {
        addv[rt<<1]+=addv[rt];
        addv[rt<<1|1]+=addv[rt];
        maxv[rt<<1]+=addv[rt];
        maxv[rt<<1|1]+=addv[rt];
        addv[rt]=0;
    }
}
void build(int l,int r,int rt)
{
    maxv[rt]=addv[rt]=0;
    if(l==r) return ;
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
}
void Update(int L,int R,int l,int r,int rt,int v)
{
    if(l>=L&&r<=R)
    {
        addv[rt]+=v;
        maxv[rt]+=v;
        return ;
    }
    PushDown(rt);
    int m=(l+r)>>1;
    if(m>=L) Update(L,R,l,m,rt<<1,v);
    if(m<R) Update(L,R,m+1,r,rt<<1|1,v);
    PushUp(rt);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n,m,p,q;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d%d%d",&n,&m,&p,&q);
        memset(shot,0,sizeof(shot));
        for(int i=0;i<=n;++i) shot[i].clear();
        int k,L,R,last;
        scanf("%d",&k);
        while(k--)
        {
            scanf("%d%d",&L,&R);
            shot[L].push_back(make_pair(R,min(R+q-1,m)));
        }
        for(int i=1;i<=n;++i)
            sort(shot[i].begin(),shot[i].end());
        build(1,m,1);
        double ans=0,r=1.0/(n-p+1);
        for(int i=1;i<=n;++i)
        {
            if(i<=n)
            {
                last=0;
                for(int j=0;j<(int)shot[i].size();++j)
                {
                    L=shot[i][j].first;
                    R=shot[i][j].second;
                    if(R<=last) continue;
                    L=max(L,last+1);
                    Update(L,R,1,m,1,1);
                    last=R;
                }
            }
            if(i>=p)
            {
                k=i-p;
                if(k)
                {
                    last=0;
                    for(int j=0;j<(int)shot[k].size();++j)
                    {
                        L=shot[k][j].first;
                        R=shot[k][j].second;
                        if(R<=last) continue;
                        L=max(L,last+1);
                        Update(L,R,1,m,1,-1);
                        last=R;
                    }
                }
                ans+=r*maxv[1];
            }
        }
        printf("%.2lf\n",ans);
    }
    return 0;
}
