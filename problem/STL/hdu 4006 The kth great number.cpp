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
    int n,k;
    char ss[2];
    while(~scanf("%d%d",&n,&k))
    {
        priority_queue<ll,vector<ll>, greater<ll> >q;
        ll num=Inf,tmp;
        for(int i=1;i<=n;++i)
        {
            scanf("%s",ss);
            if(ss[0]=='I')
            {
                scanf("%I64d",&tmp);
                q.push(tmp);
                if(q.size()>k)
                  q.pop();
            }
            else
               printf("%I64d\n",q.top());
        }
    }
    return 0;
}
