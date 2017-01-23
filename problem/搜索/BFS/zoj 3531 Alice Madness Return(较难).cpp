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
const int dirx[4]={0,0,1,-1};
const int diry[4]={1,-1,0,0};
struct Point
{
    int x,y;
    Point(){}
    Point(int x,int y):x(x),y(y){}
    bool operator ==(const Point &a) const
    {
        return x==a.x&&y==a.y;
    }
};
struct Node
{
    Point a,b;
    int know,st;
    Node(){}
    Node(Point a,Point b,int know,int st):a(a),b(b),know(know),st(st){}
};
char mat[11][11],kstr[5];
int d[10][10][10][10][25][1<<5],msk[11][11],kdir,knum,m,n,M;
Point sp1,sp2,ep1,ep2,kp,kmove[25];
vector<Node>mt[25];
inline bool check(Point p)
{
    return p.x>=0&&p.x<m&&p.y>=0&&p.y<n&&mat[p.x][p.y]!='R';
}
void getkmove()
{
    kmove[0]=kp;
    knum=1;
    int dir=kdir;
    Point pt;
    while(true)
    {
        pt.x=kmove[knum-1].x+dirx[dir];
        pt.y=kmove[knum-1].y+diry[dir];
        if(check(pt)) kmove[knum]=pt;
        else kmove[knum]=kmove[knum-1],dir^=1;
        if(kp==kmove[knum]&&kdir==dir) break;
        knum++;
    }
}
int solve()
{
    memset(d,0xff,sizeof(d));
    queue<Node>q;
    q.push(Node(sp1,sp2,0,0));
    d[sp1.x][sp1.y][sp2.x][sp2.y][0][0]=0;
    Node node;
    int state,snew,dis,kpos,knew;
    Point ma,mb;
    while(!q.empty())
    {
        node=q.front();q.pop();
        sp1=node.a;sp2=node.b;
        kpos=node.know;state=node.st;
        if(sp1==ep1&&sp2==ep2) continue;
        if(sp2==ep1&&sp1==ep2) continue;
        for(int i=0;i<4;++i)
        {
            ma.x=sp1.x+dirx[i];
            ma.y=sp1.y+diry[i];
            mb.x=sp2.x+dirx[i^1];
            mb.y=sp2.y+diry[i^1];
            dis=d[sp1.x][sp1.y][sp2.x][sp2.y][kpos][state];
            if((!check(ma))||ma==sp2||ma==kmove[kpos]) continue;
            if((!check(mb))||mb==ma||mb==kmove[kpos]) mb=sp2;
            snew=state|msk[ma.x][ma.y];
            if(mat[ma.x][ma.y]=='E'&&mat[mb.x][mb.y]=='E')
            {
                if(snew==(1<<M)-1) return dis+1;
                else continue;
            }
            knew=kpos+1;
            if(knew==knum) knew=0;
            if(kmove[knew]==ma||kmove[knew]==mb) continue;
            if(d[ma.x][ma.y][mb.x][mb.y][knew][snew]==-1)
            {
                d[ma.x][ma.y][mb.x][mb.y][knew][snew]=dis+1;
                q.push(Node(ma,mb,knew,snew));
            }
        }
    }
    return -1;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d",&m,&n))
    {
        ep1.x=-1;
        M=0;
        memset(msk,0,sizeof(msk));
        for(int i=0;i<m;++i)
        {
            scanf("%s",mat[i]);
            for(int j=0;j<n;++j)
            {
                if(mat[i][j]=='K') kp=Point(i,j);
                else if(mat[i][j]=='A') sp1=Point(i,j);
                else if(mat[i][j]=='B') sp2=Point(i,j);
                else if(mat[i][j]=='E'&&ep1.x==-1) ep1=Point(i,j);
                else if(mat[i][j]=='E') ep2=Point(i,j);
                else if(mat[i][j]=='M') msk[i][j]=(1<<M),M++;
            }
        }
        scanf("%s",kstr);
        if(kstr[0]=='E') kdir=0;
        else if(kstr[0]=='W') kdir=1;
        else if(kstr[0]=='S') kdir=2;
        else kdir=3;
        getkmove();
        int ans=solve();
        printf("%d\n",ans);
    }
    return 0;
}
