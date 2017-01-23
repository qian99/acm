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
const int maxn=200000+10;
struct Node
{
    int val,pos;
    Node(){};
    Node(int v,int p){val=v;pos=p;};
}node[maxn];
int num[maxn],sum[maxn],head,fail,ans,l,r,k;
void Inq(Node nd)
{
    while(fail>head&&node[fail-1].val>=nd.val) fail--;
    node[fail++]=nd;
}
void Outq(Node nd)
{
    while(head<fail&&node[head].pos<nd.pos-k) head++;
    int tmp=nd.val-node[head].val;
    if(tmp>ans)
    {
        ans=nd.val-node[head].val;
        l=node[head].pos+1;r=nd.pos;
    }
    else if(tmp==ans)
    {
        if(node[head].pos+1<l)
            {l=node[head].pos+1;r=nd.pos;}
        else if(node[head].pos+1==l&&(r-l>nd.pos-node[head].pos-1))
            {l=node[head].pos+1;r=nd.pos;}
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&k);
        int tmp;
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&tmp);
            num[i]=num[n+i]=tmp;
        }
        sum[0]=0;
        for(int i=1;i<=n*2;++i)
            sum[i]=(sum[i-1]+num[i]);
        head=fail=0;ans=-inf;
        Inq(Node(0,0));
        for(int i=1;i<=n*2;++i)
        {
            Outq(Node(sum[i],i));
            Inq(Node(sum[i],i));
        }
        r%=n;
        if(r==0) r=n;
        printf("%d %d %d\n",ans,l,r);
    }
    return 0;
}

