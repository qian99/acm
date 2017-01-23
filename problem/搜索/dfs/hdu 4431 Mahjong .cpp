#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn=50;
const char *mach[]={"1m","2m","3m","4m","5m","6m","7m","8m","9m",
                    "1s","2s","3s","4s","5s","6s","7s","8s","9s",
                    "1p","2p","3p","4p","5p","6p","7p","8p","9p",
                    "1c","2c","3c","4c","5c","6c","7c"};
int pa[maxn];
char st[5];
int ans[50],cnt[50],c;
bool vis[50];
inline int getnum()
{
    for(int i=0;i<34;++i)
      if(st[0]==mach[i][0]&&st[1]==mach[i][1])
        return i;
    return -1;
}
void dfs(int s)
{
    if(s==1)
    {
        for(int i=0;i<34;++i)
        {
            if(pa[i]==1&&cnt[i]<4&&!vis[i])
            {
                vis[i]=true;
                ans[c++]=i;
            }
        }
        return;
    }
    if(s==2)
    {
        for(int i=0;i<27;i+=9)
        {

            for(int j=i;j<i+9;++j)
            {
                if(pa[j]>=2&&cnt[j]<4&&!vis[j])
                {
                    vis[j]=true;
                    ans[c++]=j;
                }
                if(j<i+7)
                {
                    if(pa[j]>0&&pa[j+1]>0&&cnt[j+2]<4&&!vis[j+2])
                    {
                        vis[j+2]=true;
                        ans[c++]=j+2;
                    }
                    if(pa[j+1]>0&&pa[j+2]>0&&cnt[j]<4&&!vis[j])
                    {
                        vis[j]=true;
                        ans[c++]=j;
                    }
                    if(pa[j]>0&&pa[j+2]>0&&cnt[j+1]<4&&!vis[j+1])
                    {
                        vis[j+1]=true;
                        ans[c++]=j+1;
                    }
                }
            }
        }
        for(int i=27;i<34;++i)
        {
            if(pa[i]>=2&&cnt[i]<4&&!vis[i])
            {
                vis[i]=true;
                ans[c++]=i;
            }
        }
        return ;
    }
    if(s==4)
    {
        for(int i=0;i<34;++i)
        {
            if(pa[i]>=2)
            {
                pa[i]-=2;
                dfs(s-2);
                pa[i]+=2;
            }
        }
    }
    for(int i=0;i<27;i+=9)
    {
        for(int j=i;j<i+9;++j)
        {
            if(pa[j]>=3)
            {
                pa[j]-=3;
                dfs(s-3);
                pa[j]+=3;
            }
            if(j<i+7)
            {
                if(pa[j]>0&&pa[j+1]>0&&pa[j+2]>0)
                {
                    pa[j]--;pa[j+1]--;pa[j+2]--;
                    dfs(s-3);
                    pa[j]++;pa[j+1]++;pa[j+2]++;
                }
            }
        }
    }
    for(int i=27;i<34;++i)
    {
        if(pa[i]>=3)
        {
            pa[i]-=3;
            dfs(s-3);
            pa[i]+=3;
        }
    }
}
bool check()
{
    int ct=0;
    for(int i=0;i<34;++i)
      if(pa[i]==2) ct++;
    if(ct==7) return true;
    bool flag=false;
    if(!(pa[0]>0&&pa[8]>0&&pa[9]>0&&pa[17]>0&&pa[18]>0&&pa[26]>0))
      return false;
    for(int i=27;i<34;++i)
    {
        if(pa[i]>1) flag=true;
        if(pa[i]==0) return false;
    }
    if(pa[0]>1||pa[8]>1||pa[9]>1||pa[17]>1||pa[18]>1||pa[26]>1)
      flag=true;
    return flag;
}
int main()
{
    //freopen("in.txt","r",stdin);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        memset(pa,0,sizeof(pa));
        memset(cnt,0,sizeof(cnt));
        memset(vis,0,sizeof(vis));
        int tmp;
        for(int i=0;i<13;++i)
        {
            scanf("%s",st);
            tmp=getnum();
            pa[tmp]++;
            cnt[tmp]++;
        }
        c=0;
        dfs(13);
        for(int i=0;i<34;++i)
        {
            if(pa[i]==4) continue;
            pa[i]++;
            if(!vis[i]&&check())
            {
                vis[i]=true;
                ans[c++]=i;
            }
            pa[i]--;
        }
        sort(ans,ans+c);
        if(c==0)
          printf("Nooten\n");
        else
        {
            printf("%d",c);
            for(int i=0;i<c;++i)
              printf(" %s",mach[ans[i]]);
            printf("\n");
        }
    }
    return 0;
}
