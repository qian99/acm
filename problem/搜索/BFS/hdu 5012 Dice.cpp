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
const int R[4][7] =
{
    {0,4,3,1,2,5,6},
    {0,3,4,2,1,5,6},
    {0,6,5,3,4,1,2},
    {0,5,6,3,4,2,1}
};
const int p[7] = {0,100000,10000,1000,100,10,1};
map<pair<int,int>,int>mp;
inline int convert(int a[7])
{
    int res = 0;
    for(int i = 1;i <= 6;++i)
        res += a[i]*p[i];
    return res;
}
int changes(int x,int dir)
{
    int a[7],b[7];
    for(int i = 1;i <= 6;++i)
        a[i] = (x/p[i])%10;
    for(int i = 1;i <= 6;++i)
        b[i] = a[R[dir][i]];
    return convert(b);
}
int bfs(int x,int y)
{
    queue<pair<pair<int,int>,int> >q;
    mp.clear();
    pair<int,int>pii,np;
    pii = make_pair(x,y);
    q.push(make_pair(pii,0));
    int d;
    while(!q.empty())
    {
        pii = q.front().first;
        d = q.front().second;
        q.pop();
        if(pii.first == pii.second)
            return d;
        for(int i = 0;i < 4;++i)
        {
            np.first = changes(pii.first,i);
            np.second = pii.second;
            if(mp.find(np) == mp.end())
            {
                mp[np] = 1;
                q.push(make_pair(np,d+1));
            }
            np.first = pii.first;
            np.second = changes(pii.second,i);
            if(mp.find(np) == mp.end())
            {
                mp[np] = 1;
                q.push(make_pair(np,d+1));
            }
        }
    }
    return -1;
}
int main()
{
//    freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int a[7],b[7];
    while(~scanf("%d",&a[1]))
    {
        for(int i = 2;i <= 6;++i)
            scanf("%d",&a[i]);
        for(int j = 1;j <= 6;++j)
            scanf("%d",&b[j]);
        int x = convert(a);
        int y = convert(b);
        int ans = bfs(x,y);
        printf("%d\n",ans);
    }
    return 0;
}
