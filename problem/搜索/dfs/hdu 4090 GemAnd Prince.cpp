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
const int move[8][2]={{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
int a[10][10],n,m,k;
int save[50][10][10],ans;
bool vis[50][10][10];
int cnt[10];
inline bool check(int x,int y,int c)
{
    return x>=0&&x<n&&y>=0&&y<m&&a[x][y]==c;
}
int find(int x,int y,int step)
{
    int sum=0,c=a[x][y];
    int px,py,tmp;
    for(int i=0;i<8;++i)
    {
        px=x+move[i][0];
        py=y+move[i][1];
        if(check(px,py,c))
         sum++;
        if(sum>=2) break;
    }
    if(sum<2) return 0;
    queue<int>q;
    sum=0;
    vis[step][x][y]=true;
    tmp=x*100+y;
    q.push(tmp);
    while(!q.empty())
    {
        tmp=q.front();q.pop();
        x=tmp/100;y=tmp%100;
        for(int i=0;i<8;++i)
        {
            px=x+move[i][0];
            py=y+move[i][1];
            if(check(px,py,c))
            {
                sum++;
                a[px][py]=0;
                vis[step][px][py]=true;
                tmp=px*100+py;
                q.push(tmp);
            }
        }
    }
    return sum;
}
void getstate()
{
    for(int j=0;j<m;++j)
      for(int i=n-1;i>=0;--i)
        if(a[i][j]==0)
        {
            int k=i;
            while(a[k][j]==0&&k>0) {k--;}
            a[i][j]=a[k][j];a[k][j]=0;
        }
    for(int j=0;j<m;++j)
      if(a[n-1][j]==0)
      {
          int k=j;
          while(a[n-1][k]==0&&k<m-1) {k++;}
          for(int i=0;i<n;++i)
          {
              a[i][j]=a[i][k];
              a[i][k]=0;
          }
      }
}
void restore(int step)
{
    for(int i=0;i<n;++i)
      for(int j=0;j<m;++j)
        a[i][j]=save[step][i][j];
}
void dfs(int points,int step)
{
    ans=max(ans,points);
    memset(cnt,0,sizeof(cnt));
    for(int i=0;i<n;++i)
      for(int j=0;j<m;++j)
      {
          save[step][i][j]=a[i][j];
          cnt[a[i][j]]++;
      }
    int tmp=0;
    for(int i=1;i<=k;++i)
      if(cnt[i]>=3) tmp+=(cnt[i]*cnt[i]);
    if(points+tmp<ans) return ;
    memset(vis[step],0,sizeof(vis[step]));
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<m;++j)
        {
            if(!vis[step][i][j]&&a[i][j]&&(tmp=find(i,j,step)))
            {
                getstate();
                dfs(points+tmp*tmp,step+1);
                restore(step);
            }
        }
    }
}

int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d%d",&n,&m,&k))
    {
        for(int i=0;i<n;++i)
          for(int j=0;j<m;++j)
            scanf("%d",&a[i][j]);
        ans=0;
        dfs(0,0);
        printf("%d\n",ans);
    }
    return 0;
}
