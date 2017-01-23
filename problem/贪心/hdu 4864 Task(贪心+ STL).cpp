#include<cstdio>
#include<iostream>
#include<string>
#include<cmath>
#include<set>
#include<map>
#include<queue>
#include<cstring>
#include<algorithm>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL;
using namespace std;
typedef long long ll;
const int maxn=100000+10;
struct Node
{
    int x,y;
    Node(int x=0,int y=0):x(x),y(y){}
    bool operator <(const Node &a) const
    {
        return (x==a.x&&y>a.y)||(x>a.x);
    }
}machine[maxn],task[maxn];
map<Node,int>mp;
bool cmp(Node b,Node a)
{
    return (b.y==a.y&&b.x<a.x)||(b.y<a.y);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        mp.clear();
        for(int i=0;i<n;++i)
            scanf("%d%d",&machine[i].x,&machine[i].y);
        for(int i=0;i<m;++i)
            scanf("%d%d",&task[i].x,&task[i].y);
        sort(machine,machine+n,cmp);
        sort(task,task+m,cmp);
        int pos=0;
        Node node;
        int cnt=0;
        ll ans=0;
        map<Node,int>:: iterator it;
        for(int i=0;i<n;++i)
        {
            while(pos<m&&task[pos].y<=machine[i].y)
            {
                mp[task[pos]]++;
                pos++;
            }
            it=mp.lower_bound(machine[i]);
            if(it!=mp.end())
            {
                node=(*it).first;
                cnt++;
                ans+=500LL*node.x+2*node.y;
                if((*it).second==1) mp.erase(node);
                else (*it).second--;
            }
        }
        printf("%d %I64d\n",cnt,ans);
    }
    return 0;
}
