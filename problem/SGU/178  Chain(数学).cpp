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
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    ll n;
    cin>>n;
    int cnt=0;
    ll sum,tmp;
    while(true)
    {
        sum=cnt+1;
        tmp=cnt+1;
        for(int i=0;i<cnt;++i)
        {
            sum+=tmp*2+1;
            tmp*=2;
        }
        if(sum>=n) break;
        cnt++;
    }
    cout<<cnt<<endl;
    return 0;
}
