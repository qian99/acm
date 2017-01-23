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
const int maxn = 600000 + 10;
map<string,int>mp;
string s1,s2,str[100000 + 10];
vector<int>G[maxn];
int rnt[maxn],len[maxn],best[maxn];
bool vis[maxn];
struct Node
{
    int a,b,id;
    Node(int a = 0,int b = 0,int id = 0):a(a),b(b),id(id){}
    bool operator < (const Node & x) const
    {
        return (a == x.a && b > x.b) || (a > x.a);
    }
};
priority_queue<Node>q;
queue<int>que;
inline void cal(int id,string s)
{
    len[id] = s.length();
    rnt[id] = 0;
    for(int i = 0;i < len[id];++i)
        if(s[i] == 'r') rnt[id]++;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int m,n,cnt = 0;
    cin>>m;
    for(int i = 1;i <= m;++i)
    {
        cin>>s1;

        int l = s1.length();
        for(int j = 0;j < l;++j)
            if(s1[j] >= 'A' && s1[j] <= 'Z')
                s1[j] += 'a' - 'A';
        str[i] = s1;
        if(mp.find(s1) == mp.end())
        {
            cnt++;
            mp[s1] = cnt;
            cal(cnt,s1);
        }
    }
    cin>>n;
    int a,b;
    for(int i = 0;i < n;++i)
    {
        cin>>s1>>s2;
        int l = s1.length();
        for(int j = 0;j < l;++j)
            if(s1[j] >= 'A' && s1[j] <= 'Z')
                s1[j] += 'a' - 'A';
        l = s2.length();
        for(int j = 0;j < l;++j)
            if(s2[j] >= 'A' && s2[j] <= 'Z')
                s2[j] += 'a' - 'A';
        if(mp.find(s1) == mp.end())
        {
            cnt++;
            mp[s1] = cnt;
            cal(cnt,s1);
        }
        if(mp.find(s2) == mp.end())
        {
            cnt++;
            mp[s2] = cnt;
            cal(cnt,s2);
        }
        a = mp[s1];
        q.push(Node(rnt[a],len[a],a));
        b = mp[s2];
        q.push(Node(rnt[b],len[b],b));
        G[b].push_back(a);
    }
    for(int i = 1;i <= cnt;++i)
        best[i] = i;
    Node node;
    while(!q.empty())
    {
        node = q.top();q.pop();
        if(vis[node.id]) continue;
        que.push(node.id);
        while(!que.empty())
        {
            int u = que.front();que.pop();
            if(vis[u]) continue;
            vis[u] = true;
            for(int i = 0;i < (int)G[u].size();++i)
            {
                int v = G[u][i];
                if(vis[v]) continue;
                best[v] = node.id;
                que.push(v);
            }
        }
    }
    ll ans1 = 0,ans2 = 0;
    for(int i = 1;i <= m;++i)
    {
        int id = mp[str[i]];
        if(rnt[best[id]] < rnt[id] || (rnt[best[id]] == rnt[id] && len[best[id]] < len[id]))
        {
            id = best[id];
        }
        ans1 += rnt[id];
        ans2 += len[id];
    }
    cout<<ans1<<" "<<ans2<<endl;
    return 0;
}
