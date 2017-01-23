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
const int maxn=200000+10;
const int base=100000;
int parents[maxn],sum[maxn],num[maxn];
int Find(int x)
{
    if(x!=parents[x])
    {
        parents[x]=Find(parents[x]);
    }
    return parents[x];
}
void Uion(int x,int y)
{
    int a=Find(x);
    int b=Find(y);
    if(a!=b)
    {
        parents[b]=a;
        sum[a]+=sum[b];
        sum[b]=0;
        num[a]+=num[b];
        num[b]=0;
    }
}
void Move(int x,int y)
{
    int a=Find(x);
    int b=Find(y);
    if(a!=b)
    {
        parents[x]=b;
        num[a]--;
        num[b]++;
        sum[b]+=x;
        sum[a]-=x;
    }
}
void Init(int n)
{
    for(int i=0;i<=n;++i)
    {
        parents[i]=i+base;
        parents[i+base]=i+base;
        sum[i+base]=i;
        num[i+base]=1;
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(cin>>n>>m)
    {
        Init(n);
        int type,p,q;
        for(int i=0;i<m;++i)
        {
            cin>>type;
            if(type==1)
            {
                cin>>p>>q;
                Uion(p,q);
            }
            else if(type==2)
            {
                cin>>p>>q;
                Move(p,q);
            }
            else
            {
                cin>>p;
                cout<<num[Find(p)]<<" "<<sum[Find(p)]<<endl;
            }
        }
    }
    return 0;
}
