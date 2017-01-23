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
const int maxn = 3000 + 10;
struct Node
{
    int first,second,d;
    Node(int first = 0,int second = 0,int d = 0):first(first),second(second),d(d){}
};
int n,k,p[maxn],x[maxn],y[maxn],ans;
queue<Node>q;
bool vis[maxn][maxn];
void bfs()
{
    if(n == 1)
    {
        ans = 1;
        return;
    }
    ans = 0;
    q.push(Node(1,2,0));
    Node node;
    int a,b,c;
    while(!q.empty())
    {
        node = q.front();q.pop();
        a = node.first;
        b = node.second;
        c = node.d;
        if(c > k || vis[a][b]) continue;
//        cout<<a<<" "<<b<<endl;
        vis[a][b] = true;
        ans++;
        if(b > n || a == b) continue;
        if(y[b] == 0 && p[a] > 0)
            if(!vis[a][b+1]) q.push(Node(a,b+1,c+1));
        if(x[b] > 0 && p[a] != 100)
            if(!vis[b][b+1]) q.push(Node(b,b+1,c+1));
        if(x[b] > 0 && p[a] > 0)
            if(!vis[b+1][b+2]) q.push(Node(b+1,b+2,c+1));
    }
}
int main()
{
//    freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%d%d",&n,&k);
    for(int i = 1;i <= n;++i)
        scanf("%d",&p[i]);
    for(int i = n; i >= 1;--i)
    {
        x[i] = x[i+1];
        y[i] = y[i+1];
        if(p[i] > 0) x[i]++;
        if(p[i] == 100) y[i]++;
    }
    bfs();
    printf("%d\n",ans);
    return 0;
}
