#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<cmath>
#include<vector>
#include<queue>
#include<stack>
#define inf 0x3f3f3f3f
using namespace std;
typedef long long ll;
const int maxn=20000+10;
struct Node
{
    int val,pos;
    int type;
    bool operator <(const Node &a) const
    {
        return (val==a.val&&type<a.type)||val<a.val;
    }
};
Node a[maxn<<1];
bool flag[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    memset(flag,0,sizeof(flag));
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;++i)
    {
        scanf("%d",&a[i*2].val);
        a[i*2].type=0;a[i*2].pos=i;
        scanf("%d",&a[i*2+1].val);
        a[i*2+1].type=1;a[i*2+1].pos=i;
    }
    sort(a,a+n*2);
    queue<int>q;
    int ans=0;
    for(int i=0;i<n*2;++i)
    {
        if(a[i].type==0)
        {
            q.push(a[i].pos);
        }
        else
        {
            int tmp=q.front();
            if(tmp!=a[i].pos&&!flag[tmp])
            {
                ans++;
                flag[a[i].pos]=true;
                continue;
            }
            q.pop();
        }
        while(!q.empty())
        {
            int x=q.front();
            if(flag[x]) q.pop();
            else break;
        }
    }
    printf("%d\n",ans);
    return 0;
}
