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
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=2000+10;
struct Node
{
    int h,m;
    Node(int h=0,int m=0):h(h),m(m){}
    bool operator <(const Node &a) const
    {
        return h<a.h;
    }
}node[2][maxn];
int n,x,a,b;
int cal(int type)
{
    priority_queue<int>q[2];
    int s1=0,s2=0,X=x;
    while(s1<a&&node[0][s1].h<=X) q[0].push(node[0][s1].m),s1++;
    while(s2<b&&node[1][s2].h<=X) q[1].push(node[1][s2].m),s2++;
    int cnt=0;
    while(true)
    {
        if(!q[type].empty())
        {
            int val=q[type].top();q[type].pop();
            cnt++;
            X+=val;
            while(s1<a&&node[0][s1].h<=X) q[0].push(node[0][s1].m),s1++;
            while(s2<b&&node[1][s2].h<=X) q[1].push(node[1][s2].m),s2++;
        }
        else break;
        type^=1;
    }
    return cnt;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%d%d",&n,&x);
    a=b=0;
    int type,h,m;
    for(int i=0;i<n;++i)
    {
        scanf("%d%d%d",&type,&h,&m);
        if(type) node[1][b++]=Node(h,m);
        else node[0][a++]=Node(h,m);
    }
    sort(node[0],node[0]+a);
    sort(node[1],node[1]+b);
    int ans=0;
    ans=max(cal(0),cal(1));
    printf("%d\n",ans);
    return 0;
}