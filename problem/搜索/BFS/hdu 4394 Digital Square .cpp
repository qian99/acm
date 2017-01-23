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
bool IsSqrt(ll p)
{
    ll tmp=(sqrt(p)+eps);
    return tmp*tmp==p;
}
ll p[25];
struct Node
{
    int len;
    ll val;
    Node(int len=0,ll val=0):len(len),val(val){}
    bool operator <(const Node &a) const
    {
        return (len==a.len&&val>a.val)||(len>a.len);
    }
};
bool check(int len,ll val,ll x)
{
    val=val*val;
    for(int i=0;i<len;++i)
    {
        if(x%10!=val%10) return false;
        x/=10;
        val/=10;
    }
    return true;
}
ll bfs(int n,int L)
{
    priority_queue<Node>q;
    for(int i=0;i<=9;++i)
        if(check(1,i,n)) q.push(Node(1,i));
    int len;
    ll val;
    while(!q.empty())
    {
        len=q.top().len;
        val=q.top().val;
        q.pop();
        if(check(L,val,n)) return val;
        for(int i=0;i<=9;++i)
        {
            if(check(len+1,val+i*p[len],n))
            {
                q.push(Node(len+1,val+i*p[len]));
            }
        }
    }
    return -1;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    p[0]=1;
    for(int i=1;i<20;++i) p[i]=p[i-1]*10;
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n;
        ll m=-1;
        scanf("%d",&n);
        int tmp=n,L=0;
        while(tmp)
        {
            tmp/=10;
            L++;
        }
        m=bfs(n,L);
        if(m<0) printf("None\n");
        else printf("%I64d\n",m);
    }
    return 0;
}
