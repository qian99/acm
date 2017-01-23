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
const int maxn=100+10;
int a[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(cin>>n)
    {
        for(int i=1;i<=n;++i)
            cin>>a[i];
        int ans=0,sum;
        for(int i=1;i<=n;++i)
        {
            sum=0;
            for(int j=1;j<=n;++j)
                if(i!=j&&a[j]==i) sum++;
            ans=max(sum,ans);
        }
        cout<<ans<<endl;
    }
    return 0;
}