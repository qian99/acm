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
const int maxn=100+10;
struct Node
{
    int T,L;
    bool operator <(const Node &a) const
    {
        return L>a.L;
    }
}node[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    cin>>n;
    for(int i=0;i<n;++i)
        cin>>node[i].T;
    for(int i=0;i<n;++i)
        cin>>node[i].L;
    sort(node,node+n);
    int now=0,ans=0;
    for(int i=0;i<n;++i)
    {
        now+=node[i].T;
        if(now+node[i].L>ans)
            ans=now+node[i].L;
    }
    cout<<ans<<endl;
    return 0;
}
