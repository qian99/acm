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
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
map<int,int>mpx,mpy;
map<pair<int,int>,int>val;
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t,tcase = 0;
    scanf("%d",&t);
    while(t--)
    {
        mpx.clear();
        mpy.clear();
        val.clear();
        int n,m,k;
        int x,y,c;
        scanf("%d%d%d",&n,&m,&k);
        for(int i = 0;i < k;++i)
        {
            scanf("%d%d%d",&x,&y,&c);
            val[make_pair(x,y)] = c;
            mpx[x] = x;
            mpy[y] = y;
        }
        int q,a,b;
        scanf("%d",&q);
        printf("Case #%d:\n",++tcase);
        while(q--)
        {
            scanf("%d%d%d",&c,&a,&b);
            if(c == 1)
            {
                if(mpx.find(a) == mpx.end()) continue;
                x = mpx[a];
                y = mpx[b];
                mpx[a] = y;
                mpx[b] = x;
            }
            else if(c == 2)
            {
                if(mpy.find(a) == mpy.end()) continue;
                x = mpy[a];
                y = mpy[b];
                mpy[a] = y;
                mpy[b] = x;
            }
            else
            {
                if(mpx.find(a) == mpy.end()) continue;
                if(mpy.find(b) == mpy.end()) continue;
                pair<int,int> pii =make_pair(mpx[a],mpy[b]);
                if(val.find(pii) == val.end()) printf("0\n");
                else printf("%d\n",val[pii]);
            }
        }
    }
    return 0;
}