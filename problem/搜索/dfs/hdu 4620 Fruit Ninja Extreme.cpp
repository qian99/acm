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
struct Node
{
    int c,tim,pos;
    int ft[11];
    bool operator < (const Node &a) const
    {
        return tim<a.tim;
    }
};
Node cuts[35];
int flag[255],S[35],cnt;
int n,m,w;
int ans[35],maxcut;
bool cancut(int x)
{
    int rnt=0;
    for(int i=0;i<cuts[x].c;++i)
    {
        if(rnt>=3) break;
        if(!flag[cuts[x].ft[i]]) rnt++;
    }
    return rnt>=3;
}
void cutit(int x,int v)
{
    for(int i=0;i<cuts[x].c;++i)
        flag[cuts[x].ft[i]]+=v;
}
void dfs(int x,int lcut)
{
    if(cnt>maxcut)
    {
        maxcut=cnt;
        for(int i=0;i<cnt;++i)
          ans[i]=S[i];
    }
    if(x==n) return ;
    if(n-x+cnt<maxcut) return ;
    if(lcut>=0&&cuts[x].tim-cuts[lcut].tim>w) return ;
    dfs(x+1,lcut);
    if(cancut(x))
    {
        S[cnt++]=cuts[x].pos;
        cutit(x,1);
        dfs(x+1,x);
        cutit(x,-1);
        cnt--;
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d%d",&n,&m,&w);
        for(int i=0;i<n;++i)
        {
            scanf("%d%d",&cuts[i].c,&cuts[i].tim);
            cuts[i].pos=i+1;
            for(int j=0;j<cuts[i].c;++j)
              scanf("%d",&cuts[i].ft[j]);
        }
        sort(cuts,cuts+n);
        memset(flag,0,sizeof(flag));
        maxcut=0;cnt=0;
        dfs(0,-1);
        printf("%d\n",maxcut);
        sort(ans,ans+maxcut);
        for(int i=0;i<maxcut;++i)
        {
            if(i>0) printf(" ");
            printf("%d",ans[i]);
        }
        if(maxcut>0) printf("\n");
    }
    return 0;
}
