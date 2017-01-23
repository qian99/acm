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
vector<int> Init(int n)
{
    vector<int>vt(n+1);
    if(n==1) vt[1]=1;
    else if(n==2)
    {
        vt[1]=3;
        vt[2]=4;
    }
    else if(n&1)
    {
        for(int i=1;i<n-1;++i) vt[i]=1;
        vt[n-1]=2;
        vt[n]=n/2+1;
    }
    else
    {
        for(int i=1;i<n;++i) vt[i]=1;
        vt[n]=n/2-1;
    }
    return vt;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    cin>>n>>m;
    vector<int>rows=Init(n);
    vector<int>cols=Init(m);
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=m;++j)
        {
            if(j!=1) cout<<" ";
            cout<<rows[i]*cols[j];
        }
        cout<<endl;
    }
    return 0;
}
