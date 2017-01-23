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
int parents[maxn],val[maxn],num[maxn],c[maxn];
struct Node
{
    int l,r;
}node[maxn];
int Find(int x)
{
    if(x==parents[x]) return x;
    int tmp=Find(parents[x]);
    val[x]^=val[parents[x]];
    parents[x]=tmp;
    return parents[x];
}
bool Uion(int x,int y,int v)
{
    int a=Find(x);
    int b=Find(y);
    if(b!=a)
    {
        parents[b]=a;
        val[b]=val[x]^val[y]^v;
        return true;
    }
    return (val[x]^val[y])==v;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    char str[5];
    map<int,int>mp;
    int n,m;
    for(int i=0;i<maxn;++i)
    {
        parents[i]=i;
        val[i]=0;
    }
    scanf("%d%d",&m,&n);
    mp.clear();
    int z=0,cnt=0;
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d%s",&node[i].l,&node[i].r,str);
        num[z++]=node[i].l-1;
        num[z++]=node[i].r;
        c[i]=(str[0]=='e')?0:1;
    }
    sort(num,num+z);
    for(int i=0;i<z;++i)
        if(mp[num[i]]==0) mp[num[i]]=++cnt;
    int x,y,ans=n;
    for(int i=1;i<=n;++i)
    {
        x=node[i].l;y=node[i].r;
        x--;
        x=mp[x];
        y=mp[y];
        if(!Uion(x,y,c[i]))
        {
            ans=i-1;
            break;
        }
    }
    printf("%d\n",ans);
    return 0;
}
