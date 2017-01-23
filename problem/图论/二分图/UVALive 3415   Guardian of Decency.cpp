#include <iostream>
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
const int maxn=500+10;
struct Students
{
    int height,sex,id;
    string music,sports;
};
Students stu[maxn];
vector<int>G[maxn];
int link[maxn];
bool used[maxn];
bool check(Students a,Students b)
{
    return abs(a.height-b.height)<=40&&a.sex!=b.sex&&a.music==b.music&&a.sports!=b.sports;
}
bool dfs(int u)
{
    for(int i=0;i<G[u].size();++i)
    {
        int v=G[u][i];
        if(!used[v])
        {
            used[v]=true;
            if(link[v]==-1||dfs(link[v]))
            {
                link[v]=u;
                return true;
            }
        }
    }
    return false;
}
int hungary(int n)
{
    int res=0;
    memset(link,0xff,sizeof(link));
    for(int i=1;i<=n;++i)
    {
        memset(used,0,sizeof(used));
        if(dfs(i)) res++;
    }
    return res;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    cin>>t;
    int N;
    while(t--)
    {
        cin>>N;
        int m=0,n=0;
        string stemp;
        for(int i=0;i<N;++i)
        {
            cin>>stu[i].height>>stemp>>stu[i].music>>stu[i].sports;
            if(stemp=="M")
            {
                stu[i].sex=1;
                stu[i].id=++n;
            }
            else
            {
                stu[i].sex=0;
                stu[i].id=++m;
            }
        }
        for(int i=0;i<=n;++i) G[i].clear();
        for(int i=0;i<N;++i)
        {
            for(int j=i+1;j<N;++j)
            {
                if(check(stu[i],stu[j]))
                {
                    if(stu[i].sex) G[stu[i].id].push_back(stu[j].id);
                    else G[stu[j].id].push_back(stu[i].id);
                }
            }
        }
        int ans=n+m-hungary(n);
        cout<<ans<<endl;
    }
    return 0;
}
