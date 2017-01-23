#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<set>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=10000+10;
int factor[5],cnt[5];
vector<ll>ans[11];
map<ll,int>mp;
ll pk[11];
void dfs(int pos,ll now,int k)
{
    if(pos==2)
    {
        if(now>=pk[k-1]&&now<pk[k]) ans[k].push_back(now);
        return ;
    }
    ll tmp=1;
    for(int i=0;i<=cnt[pos];++i)
    {
        dfs(pos+1,now*tmp,k);
        tmp*=factor[pos];
    }
}
void Init()
{
    pk[0]=1;
    for(int i=1;i<=11;++i)
        pk[i]=pk[i-1]*10;
    factor[0]=2;factor[1]=5;
    for(int i=1;i<=10;++i)
    {
        cnt[0]=cnt[1]=i;
        dfs(0,1,i);
    }

}
int cal(int x)
{
    int k=0,tmp=x;
    while(tmp)
    {
        k++;
        tmp/=10;
    }
    int res=0;
    for(int i=1;i<k;++i)
        res+=ans[i].size();
    int size=ans[k].size();
    for(int j=0;j<size;++j)
        if(x>=ans[k][j]) res++;
    return res;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    Init();
//    for(int i=1;i<=10;++i)
//    {
//        int size=ans[i].size();
//        cout<<"-----------------------------------------"<<endl;
//        cout<<i<<"......."<<endl;
//        for(int j=0;j<size;++j)
//            cout<<ans[i][j]<<endl;
//    }
    int m,n;
    while(~scanf("%d%d",&m,&n))
    {
        int ans=cal(n)-cal(m-1);
        printf("%d\n",ans);
    }
    return 0;
}
