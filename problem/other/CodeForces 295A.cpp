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
const int maxn=100000+10;
ll num[maxn],add[maxn];
ll cc[maxn];
struct Opreations
{
    int l,r;
    ll d;
}op[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m,k;
    while(cin>>n>>m>>k)
    {
        for(int i=1;i<=n;++i)
          cin>>num[i];
        int l,r;
        memset(add,0,sizeof(add));
        memset(cc,0,sizeof(cc));
        for(int i=1;i<=m;++i)
        {
            cin>>op[i].l>>op[i].r>>op[i].d;
        }
        for(int i=0;i<k;++i)
        {
            cin>>l>>r;
            cc[l]++;
            cc[r+1]--;
        }
        ll zz=0;
        for(int i=1;i<=m;++i)
        {
            zz+=cc[i];
            add[op[i].l]+=(zz*op[i].d);
            add[op[i].r+1]-=(zz*op[i].d);
        }
        ll nowv=0;
        bool first=true;
        for(int i=1;i<=n;++i)
        {
            nowv+=add[i];
            if(!first) cout<<" ";
            first=false;
            cout<<num[i]+nowv;
        }
        cout<<endl;
    }
    return 0;
}
