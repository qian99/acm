#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
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
    int x,y;
    bool operator <(const Node &a )const
    {
        return (x==a.x&&y<a.y)||(x<a.x);
    }
}node[maxn];
int n,m;
struct Invert
{
    int l,r;
    Invert(){};
    Invert(int la,int ra){l=la;r=ra;}
}now[maxn],next[maxn];
void Uion(int & cnt1,int &cnt2)
{
    cnt1=0;
    now[cnt1++]=next[0];
    for(int j=1;j<cnt2;++j)
    {
        if(next[j].l<=now[cnt1-1].r)
            now[cnt1-1]=Invert(now[cnt1-1].l,max(next[j].r,now[cnt1-1].r));
        else
            now[cnt1++]=next[j];
    }
}
bool check()
{
    sort(node,node+m);
    int i=0,cnt1=0,cnt2=0;
    if(node[0].x==1)
    {
        now[cnt1++]=Invert(1,node[0].y-1);
        while(node[i].x==1&&i<m) i++;
        if(i>=m) return true;
        if(node[i].x>node[i-1].x+1) now[cnt1-1]=Invert(1,n);
    }
    else now[cnt1++]=Invert(1,n);
    while(i<m)
    {
        cnt2=0;
        int k=0,v=node[i].x;
        if(v==n)
        {
            if(now[cnt1-1].r>node[m-1].y) return true;
            return false;
        }
        while(node[i].x==v&&i<m&&k<cnt1)
        {
            while(node[i].y<now[k].l&&i+1<m&&node[i+1].x==v) i++;
            if(i>=m) break;
            if(node[i].y<now[k].l) {next[cnt2++]=Invert(now[k].l,n);break;}
            if(node[i].y>now[k].r)
            {
                next[cnt2++]=Invert(now[k].l,node[i].y-1);
                while(k+1<cnt1&&now[k+1].r<=node[i].y-1) k++;
                k++;
            }
            else
            {
                if(node[i].y==now[k].l)
                {
                    now[k].l++;
                    if(now[k].r<now[k].l) k++;
                    i++;
                }
                else
                {
                    next[cnt2++]=Invert(now[k].l,node[i].y-1);
                    now[k].l=node[i].y+1;
                    if(now[k].r<now[k].l) k++;
                    i++;
                }
            }
        }
        if(k<cnt1)
        {
            next[cnt2++]=Invert(now[k].l,n);
        }
        if(cnt2==0) return false;
        while(i<m&&node[i].x==v) i++;
        if(i<m)
        {
            if(node[i].x>v+1)
            {
                cnt1=0;
                now[cnt1++]=Invert(next[0].l,n);
            }
            else Uion(cnt1,cnt2);
        }
    }
    return true;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d",&n,&m))
    {
        for(int i=0;i<m;++i)
            scanf("%d%d",&node[i].x,&node[i].y);
        if(check())
            printf("%d\n",n*2-2);
        else
            printf("-1\n");
    }
    return 0;
}

