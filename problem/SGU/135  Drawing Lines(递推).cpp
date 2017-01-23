#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<cmath>
#include<vector>
#include<queue>
#include<stack>
#define inf 0x3f3f3f3f
using namespace std;
typedef long long ll;
const int maxn=70000+10;
ll res[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    cin>>n;
    res[0]=1;
    ll cnt=1;
    for(int i=1;i<=n;++i)
    {
        res[i]=res[i-1]+cnt;
        cnt++;
    }
    cout<<res[n]<<endl;
    return 0;
}
