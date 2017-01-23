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
const int maxn=20000+10;
const int maxm=10000000+10;
int hash[maxm],parents[maxn<<1];
int l[maxn],r[maxn],num[maxn<<1];
bool vis[maxn<<1];
int Find(int x)
{
    return x==parents[x]?x:parents[x]=Find(parents[x]);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        int cnt=0;
        for(int i=0;i<n;++i)
        {
            scanf("%d%d",&l[i],&r[i]);
            num[cnt++]=l[i];
            num[cnt++]=r[i];
        }
        sort(num,num+cnt);
        int tmp=1;
        hash[num[0]]=tmp++;
        for(int i=1;i<cnt;++i)
          if(num[i]!=num[i-1])
          {
              if(num[i]==num[i-1]+1) hash[num[i]]=tmp++;
              else hash[num[i]]=++tmp,tmp++;
          }
        memset(vis,0,sizeof(vis));
        for(int i=0;i<=n*4;++i) parents[i]=i;
        int ans=0;
        int fa,flag;
        for(int i=n-1;i>=0;--i)
        {
            flag=false;
            for(int j=hash[r[i]];j>=hash[l[i]];j=fa-1)
            {
                fa=Find(parents[j]);
                if(!vis[fa]) flag=vis[fa]=true;
                parents[j]=hash[l[i]];
            }
            if(flag) ans++;
        }
        printf("%d\n",ans);
    }
    return 0;
}
