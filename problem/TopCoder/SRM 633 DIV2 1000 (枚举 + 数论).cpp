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
const int maxn = 500 + 10;
int gcd(int a,int b) {return b == 0?a:gcd(b,a%b);}
int lcm(int a,int b) {return a*b/gcd(a,b);}
class GCDLCMEasy
{
public:
    vector<int>graph[maxn];
    vector<int>gval[maxn];
    vector<int>lval[maxn];
    int flag[maxn],num[maxn],ans[maxn];
    bool dfs(int u)
    {
        int tmp;
        for(int i = 0;i < (int)graph[u].size();++i)
        {
            int v = graph[u][i];
            tmp = gval[u][i]*lval[u][i];
            if(tmp % num[u] != 0) return false;
            if(lval[u][i] % num[u] != 0) return false;
            if(num[u] % gval[u][i] != 0) return false;
            if(num[v] == -1 && gcd(tmp/num[u],num[u]) == gval[u][i])
            {
                num[v] = tmp/num[u];
                if(!dfs(v)) return false;
            }
            else if(tmp/num[u] != num[v])
                return false;
        }
        return true;
    }
    void mark(int u)
    {
        flag[u] = 1;
        ans[u] = num[u];
        for(int i = 0;i < (int)graph[u].size();++i)
        {
            int v = graph[u][i];
            if(flag[v]) continue;
            mark(v);
        }
    }
    string possible(int n, vector <int> A, vector <int> B, vector <int> G, vector <int> L)
    {
        int m =A.size();
        for(int i = 0;i < m;++i)
        {
            graph[A[i]].push_back(B[i]);
            gval[A[i]].push_back(G[i]);
            lval[A[i]].push_back(L[i]);
            graph[B[i]].push_back(A[i]);
            gval[B[i]].push_back(G[i]);
            lval[B[i]].push_back(L[i]);
        }
        memset(flag,0,sizeof(flag));
        memset(ans,0xff,sizeof(ans));
        for(int i = 0;i < n;++i)
        {
            if(flag[i] || graph[i].size() == 0) continue;
            int maxv = 0,minv = inf;
            for(int j = 0;j < (int)gval[i].size();++j)
            {
                maxv = max(maxv,gval[i][j]);
                minv = min(minv,lval[i][j]);
            }
            bool canit = false;
            for(int j = 1;j*maxv <= minv;++j)
            {
                memset(num,0xff,sizeof(num));
                num[i] = j*maxv;
                if(dfs(i))
                {
                    canit = true;
                    mark(i);
                    break;
                }
            }
            if(!canit)
                return "Solution does not exist";
        }
        return "Solution exists";
    }
};
int main()
{
    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n,m;
    GCDLCMEasy gd;
    vector<int>A,B,G,L;
    cin>>n>>m;
    for(int i = 0;i < m;++i)
    {
        int tmp;
        cin>>tmp;
        A.push_back(tmp);
    }
    for(int i = 0;i < m;++i)
    {
        int tmp;
        cin>>tmp;
        B.push_back(tmp);
    }
    for(int i = 0;i < m;++i)
    {
        int tmp;
        cin>>tmp;
        G.push_back(tmp);
    }
    for(int i = 0;i < m;++i)
    {
        int tmp;
        cin>>tmp;
        L.push_back(tmp);
    }
    cout<<gd.possible(n,A,B,G,L)<<endl;
    return 0;
}
