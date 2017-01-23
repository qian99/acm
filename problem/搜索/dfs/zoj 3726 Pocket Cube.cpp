#includeiostream
#includecstdio
#includecstring
#includestring
#includealgorithm
#includemap
#includequeue
#includeset
#includestack
#includecmath
#includevector
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
int n,ans;
int now[30],b[30];
int convert[6][24]=
{
    {1,3,0,2,23,22,4,5,6,7,10,11,12,13,14,15,16,17,18,19,20,21,9,8},
    {2,0,3,1,6,7,8,9,23,22,10,11,12,13,14,15,16,17,18,19,20,21,5,4},

    {0,7,2,13,4,5,6,17,14,8,10,11,12,19,15,9,16,21,18,23,20,1,22,3},
    {0,21,2,23,4,5,6,1,9,15,10,11,12,3,8,14,16,7,18,13,20,17,22,19},

    {0,1,8,14,4,3,7,13,17,9,10,2,6,12,16,15,5,11,18,19,20,21,22,23},
    {0,1,11,5,4,16,12,6,2,9,10,17,13,7,3,15,14,8,18,19,20,21,22,23}
};
int check()
{
    int rnt=0;
    bool flag=true;
    int color=now[0];
    for(int i=0;i4;++i)
      if(now[i]!=color) flag=false;
    if(flag) rnt++;
    color=now[16];
    flag=true;
    for(int i=16;i20;++i)
      if(now[i]!=color) flag=false;
    if(flag) rnt++;
    color=now[20];
    flag=true;
    for(int i=20;i24;++i)
      if(now[i]!=color) flag=false;
    if(flag) rnt++;
    color=now[4];
    flag=true;
    for(int i=0;i2;++i)
      if(now[4+i]!=colornow[4+i+6]!=color) flag=false;
    if(flag) rnt++;

    color=now[6];
    flag=true;
    for(int i=0;i2;++i)
      if(now[6+i]!=colornow[6+i+6]!=color) flag=false;
    if(flag) rnt++;

    color=now[8];
    flag=true;
    for(int i=0;i2;++i)
      if(now[8+i]!=colornow[8+i+6]!=color) flag=false;
    if(flag) rnt++;
    return rnt;
}
void rotate(int wh)
{
    for(int i=0;i24;++i)
      b[i]=now[convert[wh][i]];
    for(int i=0;i24;++i)
      now[i]=b[i];
}
void dfs(int step)
{
    if(step==n) return ;
    for(int i=0;i6;++i)
    {
        rotate(i);
        int tmp=check();
        ans=max(ans,tmp);
        dfs(step+1);
        rotate(i^1);
    }
}
int main()
{
    freopen(in.txt,r,stdin);
    freopen(out.txt,w,stdout);
    while(~scanf(%d,&n))
    {
        for(int i=0;i24;++i)
          scanf(%d,&now[i]);
        ans=check();
        dfs(0);
        printf(%dn,ans);
    }
    return 0;
}

