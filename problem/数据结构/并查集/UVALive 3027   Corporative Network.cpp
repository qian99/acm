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
const int maxn=20000+10;
int parents[maxn],dis[maxn];
int Find(int x)
{
    if(parents[x]==-1) return 0;
    int sum=0;
    sum=dis[x]+Find(parents[x]);
    return sum;
}
void Uion(int u,int v)
{
    parents[u]=v;
    dis[u]=(abs(u-v))%1000;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n;
    char s[5];
    cin>>t;
    while(t--)
    {
        cin>>n;
        for(int i=0;i<=n;++i)
        {
            parents[i]=-1;
            dis[i]=0;
        }
        int a,b;
        while(cin>>s)
        {
            if(s[0]=='O') break;
            if(s[0]=='I')
            {
                cin>>a>>b;
                Uion(a,b);
            }
            else
            {
                cin>>a;
                cout<<Find(a)<<endl;
            }
        }
    }
    return 0;
}
