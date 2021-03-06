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
const int maxn = 500000 + 10;
char str[55];
pair<int,int>prer[maxn],prec[maxn];
struct BIT
{
    int C[maxn],n;
    void Init(int n)
    {
        this->n = n;
        memset(C,0,sizeof(C));
    }
    void add(int x,int v)
    {
        for(;x <= n; x += x&-x)
            C[x] += v;
    }
    int sum(int x)
    {
//        cout<<x<<endl;
        int res = 0;
        for(;x > 0;x -= x&-x)
            res += C[x];
        return res;
    }
}row[2],col[2];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n,q;
    while(~scanf("%d%d",&n,&q))
    {
        row[0].Init(q);
        row[1].Init(q);
        col[0].Init(q);
        col[1].Init(q);
        for(int i = 0;i <= q;++i)
            prer[i] = prec[i] = make_pair(0,0);
        int p,x;
        for(int i = 1;i <= q;++i)
        {
            scanf("%s",str);
            scanf("%d",&p);
            if(str[3] == 'S')
            {
                scanf("%d",&x);
                if(str[0] == 'R')
                {
                    if(prer[p].first)
                        row[prer[p].second].add(prer[p].first,-1);
                    row[x].add(i,1);
                    prer[p] = make_pair(i,x);
                }
                else
                {
                    if(prec[p].first)
                        col[prec[p].second].add(prec[p].first,-1);
                    col[x].add(i,1);
                    prec[p] = make_pair(i,x);
                }
            }
            else
            {
                int ans = 0;
                if(str[0] == 'R')
                {
                    if(prer[p].second)
                        ans = col[0].sum(i) - col[0].sum(prer[p].first);
                    else
                        ans = n - (col[1].sum(i) - col[1].sum(prer[p].first));
                }
                else
                {
                    if(prec[p].second)
                    {
//                        cout<<row[0].sum(i)<<endl;
                        ans = row[0].sum(i) - row[0].sum(prec[p].first);
                    }
                    else
                        ans = n - (row[1].sum(i) - row[1].sum(prec[p].first));
                }
                printf("%d\n",ans);
            }
        }
    }
    return 0;
}
