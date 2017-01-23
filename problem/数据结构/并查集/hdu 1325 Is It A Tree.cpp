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
int parents[maxn],counts[maxn];
bool vis[maxn];
int Find(int x)
{
    return x!=parents[x]?parents[x]=Find(parents[x]):x;
}
bool Uion(int x,int y)
{
    x=Find(x);
    y=Find(y);
    if(x!=y)
    {
        parents[y]=x;
        return true;
    }
    return false;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int a,b,mm;
    int tcase=0;
    while(~scanf("%d%d",&a,&b))
    {
        if(a<0||b<0) break;
        tcase++;
        if(a==0&&b==0)
        {
            printf("Case %d is a tree.\n",tcase);
            continue;
        }
        for(int i=0;i<maxn;++i) parents[i]=i;
        memset(vis,0,sizeof(vis));
        memset(counts,0,sizeof(counts));
        bool flag=true;
        mm=a;
        mm=max(mm,b);
        if(a==b) flag=false;
        Uion(a,b);
        vis[a]=vis[b]=true;
        counts[b]++;
        while(~scanf("%d%d",&a,&b))
        {
            if(a==0&&b==0) break;
            counts[b]++;
            if(counts[b]>1) flag=false;
            mm=max(mm,max(a,b));
            if(a==b) flag=false;
            vis[a]=vis[b]=true;
            if(!flag) continue;
            if(!Uion(a,b)) flag=false;
        }
        if(flag)
        {
            int cnt=0;
            for(int i=0;i<=mm;++i)
            {
                if(vis[i])
                 if(parents[i]==i) cnt++;
            }
            if(cnt>1) flag=false;
        }
        if(flag)
          printf("Case %d is a tree.\n",tcase);
        else
          printf("Case %d is not a tree.\n",tcase);
    }
    return 0;
}
