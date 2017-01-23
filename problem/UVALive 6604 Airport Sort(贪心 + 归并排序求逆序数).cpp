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
#include<bitset>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 200000 + 10;
int a[maxn],b[maxn];
vector<int>num[maxn],pos[maxn];
ll X,Y;
void solve(int l,int r)
{
    if(l >= r) return ;
    int m = (l + r)>>1;
    solve(l,m);
    solve(m + 1,r);
    int x = l,y = m + 1,tot = 0;
    while(x <= m && y <= r)
    {
        if(a[x] < a[y])
            b[tot++] = a[x++];
        else
        {
            b[tot++] = a[y++];
            X += m - x + 1;
        }
    }
    while(x <= m) b[tot++] = a[x++];
    while(y <= r) b[tot++] = a[y++];
    for(int i = 0;i < tot;++i)
        a[l + i] = b[i];
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t,tcase = 0;
    scanf("%d",&t);
    while(t--)
    {
        int n,k;
        X = Y = 0;
        scanf("%d%d",&n,&k);
        for(int i = 0;i < n;++i)
        {
            num[i].clear();
            pos[i].clear();
        }
        for(int i = 0;i < n;++i)
        {
            scanf("%d",&a[i]);
            a[i]--;
            num[a[i]/k].push_back(a[i]);
            pos[a[i]/k].push_back(i);
        }
        for(int i = 0;i <= n/k + 1;++i)
        {
            int size = num[i].size();
            for(int j = 0;j < size;++j)
            {
//                cout<<num[i][j]<<endl;
                Y = max(Y,(ll)abs(pos[i][j] - (i*k + j)));
            }
            sort(num[i].begin(),num[i].end());
            for(int j = 0;j < size;++j)
            {
                a[pos[i][j]] = num[i][j];
            }
        }
        solve(0,n - 1);
        X -= Y;
        printf("Case %d: %lld\n",++tcase,X);
    }
    return 0;
}

