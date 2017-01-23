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
const int maxn=52;
struct Replace
{
    int a[maxn+1];
    bool check()
    {
        for(int i=1;i<=maxn;++i)
            if(a[i]!=i) return false;
        return true;
    }
    void change(int L,int R)
    {
        int b[maxn+1];
        for(int i=L;i<=R;++i)
            b[i-L+1]=a[i];
        for(int i=L-1;i>=1;--i)
            a[i+(R-L+1)]=a[i];
        for(int i=1;i<=(R-L+1);++i)
            a[i]=b[i];
    }
};
vector<Replace>ans;
int val[maxn+1];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    scanf("%d",&t);
    Replace rp;
    while(t--)
    {
        int n,L,R;
        for(int i=1;i<=maxn;++i)
            scanf("%d",&val[i]);
        for(int i=1;i<=maxn;++i)
            rp.a[i]=i;
        scanf("%d%d%d",&n,&L,&R);
        ans.clear();
        ans.push_back(rp);
        int cnt=1;
        while(true)
        {
            rp.change(L,R);
            if(rp.check()) break;
            cnt++;
            ans.push_back(rp);
        }
        n%=cnt;
        rp=ans[n];
        printf("Case #%d:",++tcase);
        for(int i=1;i<=maxn;++i)
            printf(" %d",val[rp.a[i]]);
        printf("\n");
    }
    return 0;
}
