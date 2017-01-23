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
const int md[14]={0,31,28,31,30,31,30,31,31,30,31,30,31};
const int maxn=1000+10;
struct Node
{
    int x,t,id;
    Node(){}
    Node(int x,int t,int id):x(x),t(t),id(id){}
    bool operator <(const Node &a) const
    {
        if(t!=a.t) return t<a.t;
        if(id==a.id) return x<a.x;
        return id<a.id;
    }
}node[maxn];
struct EX
{
    int L,R,t;
    EX(){}
    EX(int L,int R,int t):L(L),R(R),t(t){}
};
vector<EX>vt[maxn];
int cald(int mon,int day)
{
    int sum=0;
    for(int i=1;i<mon;++i)
        sum+=md[i]*24*60;
    sum+=(day-1)*24*60;
    return sum;
}
int cal(int hour,int minu)
{
    return hour*60+minu;
}
int solve(int x)
{
    int L,R,l,r,t;
    int sum=0;
    for(int i=0;i<(int)vt[0].size();++i)
    {
        L=vt[0][i].L;
        R=vt[0][i].R;
        t=vt[0][i].t;
//        EX xx=vt[x][0];
        for(int j=0;j<(int)vt[x].size();++j)
        {
            if(vt[x][j].t!=t) continue;
            l=vt[x][j].L;
            r=vt[x][j].R;
            if(l>=L&&l<=R) sum+=min(R,r)-l;
            else if(r>=L&&r<=R) sum+=r-max(l,L);
            else if(l<L&&r>R) sum+=R-L;
        }
    }
    return sum;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        int mon,day,hour,minu,idx;
        char str[5];
        for(int i=0;i<n;++i)
        {
            scanf("%d/%d %d:%d",&mon,&day,&hour,&minu);
            scanf("%s%d",str,&idx);
            node[i]=Node(cal(hour,minu),cald(mon,day),idx);
        }
        sort(node,node+n);
        for(int i=0;i<=n;++i) vt[i].clear();
        int lastday=node[0].t,last=node[0].id;
        int cnt=0;
        for(int i=0;i<n;++i)
        {
            if(node[i].t==lastday)
            {
                if(node[i].id==last)
                {
                    if(cnt&1)
                    {
                        vt[node[i].id].push_back(EX(node[i-1].x,node[i].x,lastday));
                    }
                    cnt^=1;
                }
                else
                {
                    cnt=1;
                    last=node[i].id;
                }
            }
            else
            {
                lastday=node[i].t;
                last=node[i].id;
                cnt=1;
            }
        }
        int ans=0;
        for(int i=1;i<=n;++i)
            ans=max(ans,solve(i));
        printf("%d\n",ans);
    }
    return 0;
}
