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
const int maxn=400000+10;
int parents[maxn],m,cnt;
struct Point
{
    int x,y;
    bool operator <(const Point &a) const
    {
        return (x==a.x&&y<a.y)||(x<a.x);
    }
};
int Find(int x)
{
    return parents[x]==x?x:parents[x]=Find(parents[x]);
}
bool Uion(int x,int y)
{
    int a=Find(x);
    int b=Find(y);
    if(a!=b)
    {
        parents[b]=a;
        return false;
    }
    return true;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%d",&m);
    map<Point,int>mp;
    cnt=0;
    Point a,b;
    int u,v,ans=0;
    bool flag=false;
    for(int i=0;i<=m*2;++i) parents[i]=i;
    for(int i=0;i<m;++i)
    {
        scanf("%d%d",&a.x,&a.y);
        scanf("%d%d",&b.x,&b.y);
        if(flag) continue;
        if(!mp[a]) mp[a]=++cnt;
        if(!mp[b]) mp[b]=++cnt;
        u=mp[a];v=mp[b];
        if(Uion(u,v))
        {
            ans=i+1;
            flag=true;
        }
    }
    printf("%d\n",ans);
    return 0;
}
