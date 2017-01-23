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
int parents[maxn],val[maxn];
int Find(int x)
{
    if(x==parents[x]) return x;
    int tmp=Find(parents[x]);
    val[x]=(val[x]+val[parents[x]])%3;
    parents[x]=tmp;
    return parents[x];
}
bool Uion(int x,int y,int v)
{
    int a=Find(x);
    int b=Find(y);
    if(v==1)
    {
        if(a==b) return val[x]==val[y];
        parents[b]=a;
        if(val[x]==0) val[b]=val[y]==0?0:(val[y]^3);
        if(val[x]==1) val[b]=val[y]==2?2:(val[y]^1);
        if(val[x]==2) val[b]=val[y]==1?1:(val[y]^2);
        return true;
    }
    else
    {
        if(a==b)
        {
            if(val[x]==0) return val[y]==1;
            if(val[x]==1) return val[y]==2;
            return val[y]==0;
        }
        else
        {
            parents[b]=a;
            if(val[x]==0) val[b]=val[y]==2?2:(val[y]^1);
            if(val[x]==1) val[b]=val[y]==1?1:(val[y]^2);
            if(val[x]==2) val[b]=val[y]==0?0:(val[y]^3);
            return true;
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,k;
    scanf("%d%d",&n,&k);
        int ans=0;
        for(int i=0;i<=n;++i)
        {
            parents[i]=i;
            val[i]=0;
        }
        int d,x,y;
        while(k--)
        {
            scanf("%d%d%d",&d,&x,&y);
            if(x>n||y>n)
            {
                ans++;
                continue;
            }
            if(d==1)
            {
                if(!Uion(x,y,d))
                  ans++;
            }
            else
            {
                if(x==y)
                {
                    ans++;
                    continue;
                }
                if(!Uion(x,y,d))
                  ans++;
            }
        }
        printf("%d\n",ans);
    return 0;
}
