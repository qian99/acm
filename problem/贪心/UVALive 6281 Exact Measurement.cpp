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
vector<pair<ll,int> >mass[20];
vector<int>ans;
ll pw[20],x[20];
priority_queue<pair<ll,int> >q;
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    pw[0] = 1;
    for(int i = 1;i <= 18;++i) pw[i] = pw[i-1]*10LL;
    int n;
    ll target;
    while(~scanf("%lld%d",&target,&n))
    {
        int k;
        ll num;
        for(int i = 0;i <= 18;++i)
            mass[i].clear();
        for(int i = 1;i <= n;++i)
        {
            scanf("%d%lld",&k,&num);
            mass[k].push_back(make_pair(num,i));
        }
        for(int i = 0;i <= 18;++i)
            sort(mass[i].begin(),mass[i].end());
        while(!q.empty()) q.pop();
        ans.clear();
        for(int i = 18;i >= 0;--i)
        {
            x[i] = target/pw[i];
            target -= x[i]*pw[i];
        }
        ll sum = 0;
        pair<ll,int>pii;
        for(int i = 0;i <= 18;++i)
        {
            for(int j = 0;j < (int)mass[i].size();++j)
                q.push(make_pair(mass[i][j].first*pw[i],mass[i][j].second));
            target += x[i]*pw[i];
            while(sum < target && !q.empty())
            {
                pii = q.top();q.pop();
                ans.push_back(pii.second);
                sum += pii.first;
            }
            if(sum < target)
                break;
        }
        if(sum < target)
            puts("-1");
        else
        {
            printf("%d\n",(int)ans.size());
            sort(ans.begin(),ans.end());
            for(int i = 0;i < (int)ans.size();++i)
            {
                if(i > 0) printf(" ");
                printf("%d",ans[i]);
            }
            puts("");
        }
    }
    return 0;
}
