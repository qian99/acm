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
//edges[i][j]为边(i,j)的编号，marks[i]表示边i是横边还是竖边
int edges[30][30],marks[30],p[30];
//cont[i]为后添加的边在状态中是多少位，conp[i]为后面的状态中第i位为哪条边
int dp[5000],cont[30],conp[30],len;
//selected[i]表示第i条边是否在最开始已经选了
bool selected[30];
void Init()
{
    int cnt=0;
    memset(edges,0,sizeof(edges));
    memset(marks,0,sizeof(marks));
    memset(selected,0,sizeof(selected));
    for(int i=0;i<5000;++i) dp[i]=-inf;
    for(int i=1;i<=13;i+=4)
    {
        for(int j=0;j<3;++j)
        {
            edges[i+j][i+j+1]=edges[i+j+1][i+j]=++cnt;
            marks[cnt]=1;
        }
        if(i==13) break;
        for(int j=0;j<4;++j)
          edges[i+j][i+j+4]=edges[i+j+4][i+j]=++cnt;
    }
    for(int i=0;i<30;++i) p[i]=1<<i;
}
inline bool check(int a,int b,int c,int state)
{
    if(!selected[a]&&(p[cont[a]]&state)==0) return false;
    if(!selected[b]&&(p[cont[b]]&state)==0) return false;
    if(!selected[c]&&(p[cont[c]]&state)==0) return false;
    return true;
}
int getpoints(int e,int now)
{
    int sum=0;
    int a,b,c;
    if(marks[e])
    {
        a=e-4;b=e-3;c=e-7;
        if(c>0&&check(a,b,c,now))
          sum++;
        a=e+3;b=e+4;c=e+7;
        if(a<24&&check(a,b,c,now))
          sum++;
    }
    else
    {
        a=e-4;b=e-1;c=e+3;
        if(marks[c]&&check(a,b,c,now))
          sum++;
        a=e-3;b=e+1;c=e+4;
        if(marks[a]&&check(a,b,c,now))
          sum++;
    }
    return sum;
}
int f(int state)
{
    if(state==p[len]-1) return 0;
    if(dp[state]!=-inf) return dp[state];
    dp[state]=0;
    int tmp=-inf;
    for(int i=0;i<len;++i)
    {
        if((p[i]&state)==0)
          tmp=max(tmp,getpoints(conp[i],state)-f(p[i]|state));
    }
    return dp[state]=tmp;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        Init();
        int n,a,b,e,ans=0,turns=0;
        scanf("%d",&n);
        len=24-n;
        for(int i=0;i<n;++i)
        {
            scanf("%d%d",&a,&b);
            e=edges[a][b];
            if(turns)
              ans-=getpoints(e,0);
            else ans+=getpoints(e,0);
            turns^=1;
            selected[e]=true;
        }
        int cnt=0;
        for(int i=1;i<=24;++i)
          if(!selected[i]) {conp[cnt]=i;cont[i]=cnt;cnt++;}
        if(turns)
          ans-=f(0);
        else ans+=f(0);
        printf("Case #%d: ",tcase);
        if(ans>0) puts("Tom200");
        else puts("Jerry404");
    }
    return 0;
}
