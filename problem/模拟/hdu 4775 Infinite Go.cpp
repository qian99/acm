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
#include<bitset>
#include<set>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=10000+10;
const int dirx[4]={0,1,0,-1};
const int diry[4]={1,0,-1,0};
map<pair<int,int>,int>mp,id;
set<pair<int,int> >space[maxn];
int parent[maxn];
int Find(int x)
{
    return x==parent[x]?x:parent[x]=Find(parent[x]);
}
void Uion(int x,int y)
{
    int a=Find(x);
    int b=Find(y);
    if(a!=b)
    {
        if(space[a].size()>space[b].size())
            swap(a,b);
        parent[a]=b;
        set<pair<int,int> >:: iterator it;
        it=space[a].begin();
        while(it!=space[a].end())
        {
            space[b].insert(*it);
            it++;
        }
        space[a].clear();
    }
}
int check(int x,int y)
{
    if(mp.find(make_pair(x,y))!=mp.end()) return mp[make_pair(x,y)];
    return -1;
}
void remove(int x,int y,int c)
{
    queue<pair<int,int> >q;
    q.push(make_pair(x,y));
    int dx,dy;
    while(!q.empty())
    {
        x=q.front().first;
        y=q.front().second;
        q.pop();
        mp.erase(make_pair(x,y));
        for(int i=0;i<4;++i)
        {
            dx=x+dirx[i];
            dy=y+diry[i];
            if(dx<=0||dy<=0) continue;
            if(check(dx,dy)==c)
                q.push(make_pair(dx,dy));
            else if(check(dx,dy)==(c^1))
                space[Find(id[make_pair(dx,dy)])].insert(make_pair(x,y));
        }
    }
}
void chess(int x,int y,int c)
{
    pair<int,int> u=make_pair(x,y);
    mp[u]=c;
    int dx,dy;
    for(int i=0;i<4;++i)
    {
        dx=x+dirx[i];
        dy=y+diry[i];
        if(dx<=0||dy<=0) continue;
        pair<int,int> v=make_pair(dx,dy);
        int d=check(dx,dy);
        if(d==c) Uion(id[u],id[v]);
        else if(d==(c^1))
        {
            space[Find(id[v])].erase(u);
            if(space[Find(id[v])].size()==0) remove(dx,dy,c^1);
        }
        else space[Find(id[u])].insert(v);
    }
    space[Find(id[u])].erase(u);
    if(space[Find(id[u])].size()==0)
        remove(x,y,c);
}
void Init(int n)
{
    for(int i=0;i<=n;++i)
    {
        parent[i]=i;
        space[i].clear();
    }
    mp.clear();
    id.clear();
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
        int x,y;
        Init(n);
        for(int i=1;i<=n;++i)
        {
            scanf("%d%d",&x,&y);
            id[make_pair(x,y)]=i;
            chess(x,y,i&1);
        }
        int B=0,W=0;
        map<pair<int,int> ,int>:: iterator it;
        it=mp.begin();
        while(it!=mp.end())
        {
            int c=it->second;
            if(c) B++;
            else W++;
            it++;
        }
        printf("%d %d\n",B,W);
    }
    return 0;
}
