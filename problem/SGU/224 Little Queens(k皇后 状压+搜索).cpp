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
int ans,n,N,k;
inline int lowbit(int x) {return x&-x;}
void dfs(int x,int lmsk,int rmsk,int msk,int cnt)
{
    if(cnt==k) {ans++;return ;}
    if(x==n) return ;
    int st=lmsk|rmsk|msk;
    st=(~st)&N;
    dfs(x+1,(lmsk<<1)&N,rmsk>>1,msk,cnt);
    while(st)
    {
        int tmp=lowbit(st);
        st&=(~tmp);
        dfs(x+1,((lmsk|tmp)<<1)&N,(rmsk|tmp)>>1,msk|tmp,cnt+1);
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    cin>>n>>k;
    N=(1<<n)-1;
    ans=0;
    dfs(0,0,0,0,0);
    cout<<ans<<endl;
    return 0;
}
