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
const int dir[4][2]={{-1,0},{0,-1},{1,0},{0,1}};
int n;
int getDir(char a)
{
    if(a=='N') return 0;
    if(a=='W') return 1;
    if(a=='S') return 2;
    return 3;
}
inline bool check(int x,int y)
{
    return x>0&&x<=n&&y>0&&y<=n;
}
void getres(int x,int y,int sp,int &d,int &px,int &py)
{
    int len=sp;
    len=len%(2*n-2);
    px=x;py=y;
    while(len>0)
    {
        x=px+dir[d][0];
        y=py+dir[d][1];
        if(check(x,y))
        {
            px=x;
            py=y;
        }
        else
        {
            d=(d+2)%4;
            px=px+dir[d][0];
            py=py+dir[d][1];
        }
        len--;
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    char s[5];
    int dira,dirb,spa,spb,ta,tb,k;
    int ax,ay,bx,by;
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        scanf("%s%d%d",s,&spa,&ta);
        dira=getDir(s[0]);
        scanf("%s%d%d",s,&spb,&tb);
        dirb=getDir(s[0]);
        scanf("%d",&k);
        ax=ay=1;bx=by=n;
        int nowt=0,tmp,px,py;
        while(nowt<k)
        {
            if(ax==bx&&ay==by)
            {
                tmp=dira;
                dira=dirb;
                dirb=tmp;
            }
            else
            {
                if(nowt%ta==0&&nowt!=0) dira=(dira+1)%4;
                if(nowt%tb==0&&nowt!=0) dirb=(dirb+1)%4;
            }
            getres(ax,ay,spa,dira,px,py);
            ax=px;ay=py;
            getres(bx,by,spb,dirb,px,py);
            bx=px;by=py;
            nowt++;
        }
        printf("%d %d\n",ax,ay);
        printf("%d %d\n",bx,by);
    }
    return 0;
}
