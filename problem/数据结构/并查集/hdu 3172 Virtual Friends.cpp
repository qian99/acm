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
const int maxn=200000+10;
int parents[maxn],v[maxn];
int Find(int x)
{
    return x==parents[x]?x:parents[x]=Find(parents[x]);
}
int Uion(int x,int y)
{
    int a=Find(x);
    int b=Find(y);
    if(a!=b)
    {
        parents[b]=a;
        v[a]+=v[b];
        v[b]=0;
    }
    return v[a];
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n,m;
    map<string,int>mp;
    string str1,str2;
    while(cin>>t)
    {
        while(t--)
        {
            cin>>n;
            mp.clear();
            m=1;
            for(int i=0;i<maxn;++i) parents[i]=i,v[i]=1;
            int a,b;
            for(int i=0;i<n;++i)
            {
                cin>>str1>>str2;
                if(!mp[str1]) mp[str1]=m++;
                if(!mp[str2]) mp[str2]=m++;
                a=mp[str1],b=mp[str2];
                cout<<Uion(a,b)<<endl;
            }
        }
    }
    return 0;
}
