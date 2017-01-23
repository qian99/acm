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
const int maxn=1000+10;
struct Node
{
    int x1,y1,x2,y2,type;
    Node(){}
    Node(int x1,int y1,int x2,int y2,int type):x1(x1),y1(y1),x2(x2),y2(y2),type(type){}
}node[maxn];
int pre[maxn];
inline bool inSeg(int L,int R,int x)
{
    return x>=L&&x<=R;
}
inline bool inRect(int xl,int xr,int yl,int yr,int x,int y)
{
    return inSeg(xl,xr,x)&&inSeg(yl,yr,y);
}
bool check(int a,int b,int x1,int y1,int x2,int y2)
{
    if(node[a].type)
    {
        bool flag=true;
        flag&=inSeg(node[a].x1,node[a].x2,x1);
        flag&=inSeg(node[a].x1,node[a].x2,x2);
        flag&=inSeg(node[b].y1,node[b].y2,y1);
        flag&=inSeg(node[b].y1,node[b].y2,y2);
        if(flag) return (ll)(y1-node[a].y1)*(y2-node[a].y1)<0;
    }
    else
    {
        bool flag=true;
        flag&=inSeg(node[a].y1,node[a].y2,y1);
        flag&=inSeg(node[a].y1,node[a].y2,y2);
        flag&=inSeg(node[b].x1,node[b].x2,x1);
        flag&=inSeg(node[b].x1,node[b].x2,x2);
        if(flag) return (ll)(x1-node[a].x1)*(x2-node[a].x1)<0;
    }
    return false;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int x1,y1,x2,y2;
    int n,q;
    while(~scanf("%d%d%d%d",&x1,&y1,&x2,&y2))
    {
        scanf("%d%d",&n,&q);
        node[0]=Node(x1,y1,x1,y2,0);
        int c;
        for(int i=1;i<=n;++i)
        {
            scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
            c=(y1==y2);
            if(x1>x2) swap(x1,x2);
            if(y1>y2) swap(y1,y2);
            node[i]=Node(x1,y1,x2,y2,c);
            for(int j=i-1;j>=0;--j)
                if(node[j].type!=c)
                {
                    if(c)
                    {
                        if(y1>=node[j].y1&&y1<=node[j].y2&&(x1==node[j].x1||x2==node[j].x1))
                        {
                            pre[i]=j;
                            break;
                        }
                    }
                    else
                    {
                        if(x1>=node[j].x1&&x1<=node[j].x2&&(y1==node[j].y1||y2==node[j].y1))
                        {
                            pre[i]=j;
                            break;
                        }
                    }
                }
        }
        while(q--)
        {
            scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
            int pos=n+1;
            for(int i=1;i<=n;++i)
            {
                if(check(i,pre[i],x1,y1,x2,y2))
                {
                    pos=i;
                    break;
                }
            }
            if(node[pos].type)
            {
                x1=node[pos].x1;
                x2=node[pos].x2;
                y1=node[pre[pos]].y1;
                y2=node[pre[pos]].y2;
            }
            else
            {
                y1=node[pos].y1;
                y2=node[pos].y2;
                x1=node[pre[pos]].x1;
                x2=node[pre[pos]].x2;
            }
            if(x1>x2) swap(x1,x2);
            if(y1>y2) swap(y1,y2);
            int ans=0;
            for(int i=pos;i<=n;++i)
            {
                if(inRect(x1,x2,y1,y2,node[i].x1,node[i].y1)&&
                   inRect(x1,x2,y1,y2,node[i].x2,node[i].y2))
                {
                    ans++;
                }
            }
            printf("%d\n",n-ans+1);
        }
    }
    return 0;
}
