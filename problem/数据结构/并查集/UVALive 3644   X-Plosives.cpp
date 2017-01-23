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
const int maxn=100000+10;
int parents[maxn];
int Find(int x)
{
    if(x!=parents[x])
    {
        parents[x]=Find(parents[x]);
    }
    return parents[x];
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
    int a,b,sum=0;
    while(cin>>a)
    {
        sum=0;
        cin>>b;
        for(int i=0;i<maxn;++i)
            parents[i]=i;
        Uion(a,b);
        while(cin>>a)
        {
            if(a==-1) break;
            cin>>b;
            if(!Uion(a,b)) sum++;
        }
        cout<<sum<<endl;
    }

    return 0;
}

