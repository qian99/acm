#include <iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=1000+10;
int parents[maxn];
int sum;
int Find(int x)
{
    return x==parents[x]?x:parents[x]=Find(parents[x]);
}
void Uion(int x,int y)
{
    int a=Find(x);
    int b=Find(y);
    if(a!=b)
    {
        sum++;
        parents[b]=a;
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    cin>>t;
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        for(int i=0;i<=n;++i) parents[i]=i;
        int a,b;
        sum=0;
        for(int i=0;i<m;++i)
        {
            cin>>a>>b;
            Uion(a,b);
        }
        cout<<n-sum<<endl;
    }
    return 0;
}
