#include <iostream>
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
const int maxn=100+10;
int parents[maxn];
int l[maxn],r[maxn],w[maxn];
int v[maxn];
bool cmp(int a,int b)
{
    return w[a]<w[b];
}
int Find(int x)
{
    return x==parents[x]?x:parents[x]=Find(parents[x]);
}
bool Uion(int x,int y)
{
    int a=Find(x);
    int b=Find(y);
    if(a!=b)
    {
        parents[b]=a;
        return true;
    }
    return false;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        char s[5];
        int t,x,y,z,m=0;
        for(int i=0;i<n;++i) parents[i]=i;
        for(int i=0;i<n-1;++i)
        {
            scanf("%s%d",s,&t);
            x=s[0]-'A';
            for(int j=0;j<t;++j)
            {
                scanf("%s%d",s,&z);
                y=s[0]-'A';
                l[m]=x;r[m]=y;w[m]=z;
                m++;
            }
        }
        for(int i=0;i<m;++i) v[i]=i;
        sort(v,v+m,cmp);
        int ans=0;
        for(int i=0;i<m;++i)
        {
            if(Uion(l[v[i]],r[v[i]]))
               ans+=w[v[i]];
        }
        printf("%d\n",ans);
    }
    return 0;
}
