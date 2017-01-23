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
#include<bitset>
#include<set>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=100+10;
int a[maxn],b[maxn],n;
int getcval(char c)
{
    if(c=='R') return 0;
    if(c=='G') return 1;
    if(c=='B') return 2;
    if(c=='Y') return 3;
    if(c=='W') return 4;
    return c-'1'+5;
}
int cal(int x)
{
    int cnt=0;
    while(x)
    {
        x=x&(x-1);
        cnt++;
    }
    return cnt;
}
bool check(int msk)
{
    for(int i=0;i<n;++i)
        for(int j=i+1;j<n;++j)
        {
            int flag=0;
            if(a[i]!=a[j]&&(((msk>>a[i])&1)||((msk>>a[j])&1))) flag=1;
            if(b[i]!=b[j]&&(((msk>>b[i])&1)||((msk>>b[j])&1))) flag=1;
            if((a[i]!=a[j]||b[i]!=b[j])&&!flag) return false;
        }
    return true;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    char str[10];
    cin>>n;
    for(int i=0;i<n;++i)
    {
        cin>>str;
        a[i]=getcval(str[0]);
        b[i]=getcval(str[1]);
    }
    int ans=20;
    for(int i=0;i<(1<<10);++i)
        if(check(i)) ans=min(ans,cal(i));
    cout<<ans<<endl;
    return 0;
}
