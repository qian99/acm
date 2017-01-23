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
const int maxn=10000+10;
int L[maxn],R[maxn],degree[maxn],n,m;
map<pair<int,int> ,int>mp;
int solve()
{
    queue<int>q;
    for(int i=1;i<=n;++i)
        if(degree[i]==2) q.push(i);
    int u,maxv=0;
    pair<int,int>pii;
    while(!q.empty())
    {
        u=q.front();q.pop();
        if(degree[u]!=2) continue;
        degree[u]=0;
        int cnt1=0,cnt2=0,v1,v2;
        v1=R[u];
        cnt1=mp[make_pair(u,v1)];
        while(v1!=u)
        {
            if(degree[v1]!=2) break;
            degree[v1]=0;
            cnt1+=mp[make_pair(v1,R[v1])];
            v1=R[v1];
        }
        if(v1==u)
        {
            maxv=max(maxv,cnt1+mp[make_pair(v1,u)]);
            break;
        }
        v2=L[u];
        cnt2=mp[make_pair(u,v2)];
        while(v2!=u)
        {
            if(degree[v2]!=2) break;
            degree[v2]=0;
            cnt2+=mp[make_pair(v2,L[v2])];
            v2=L[v2];
        }
        int val=mp[make_pair(v1,v2)];
        if(val==0)
        {
            mp[make_pair(v1,v2)]=mp[make_pair(v2,v1)]=cnt1+cnt2;
            L[v1]=v2;R[v2]=v1;
        }
        else
        {
            maxv=max(maxv,cnt1+cnt2+1);
            mp[make_pair(v1,v2)]=mp[make_pair(v2,v1)]=1;
            L[v1]=v2;R[v2]=v1;
            degree[v1]--;degree[v2]--;
            if(degree[v1]==2) q.push(v1);
            if(degree[v2]==2) q.push(v2);
        }

    }
    return maxv;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d",&n,&m))
    {
        memset(degree,0,sizeof(degree));
        mp.clear();
        int x,y;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d",&x,&y);
            mp[make_pair(x,y)]=1;
            mp[make_pair(y,x)]=1;
            degree[x]++;degree[y]++;
        }
        for(int i=1;i<=n;++i)
        {
            if(i<n) mp[make_pair(i,i+1)]=mp[make_pair(i+1,i)]=1;
            degree[i]+=2;
            L[i]=i-1;
            R[i]=i+1;
        }
        mp[make_pair(n,1)]=mp[make_pair(1,n)]=1;
        L[1]=n;R[n]=1;
        int ans=solve();
        printf("%d\n",ans);
    }
    return 0;
}
