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
struct Node
{
    int cnt;
    int canbeat[10];
};
Node node[10];
int hero[10],n;
string name[10];
bool vis1[10],vis2[10];
int res[20];
bool finds,flag;
bool battle(int x,int y)
{
    for(int i=0;i<node[y].cnt;++i)
    {
        if(node[y].canbeat[i]==x)
          return false;
    }
    return true;
}
bool check()
{
    int a=0;
    int b=n;
    while(a<n&&b<2*n)
    {
        if(battle(res[a],res[b]))
           b++;
        else a++;
    }
    if(a<n) return true;
    return false;
}
void dfs2(int b)
{
    if(b<n)
    {
        for(int i=0;i<n;++i)
        {
            if(!vis2[i])
            {
                res[b+n]=i;
                vis2[i]=true;
                dfs2(b+1);
                vis2[i]=false;
                if(!flag) return;
            }
        }
    }
    if(!check()) flag=false;
}
void dfs(int a)
{
    if(a<n)
    {
        for(int i=0;i<n;++i)
        {
            if(!vis1[i])
            {
                res[a]=i;
                vis1[i]=true;
                dfs(a+1);
                vis1[i]=false;
                if(finds) return;
            }
        }
    }
    if(finds) return;
    flag=true;
    dfs2(0);
    if(flag)
    {
        finds=true;
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int tcase=0,t;
    cin>>t;
    while(t--)
    {
        cin>>n;
        tcase++;
        for(int i=0;i<n;++i)
          cin>>name[i];
        sort(name,name+n);
        map<string,int>mp;
        for(int i=0;i<n;++i)
        {
            hero[i]=i;
            mp[name[i]]=i;
        }
        string tmp;
        for(int i=0;i<n;++i)
        {
            cin>>node[i].cnt;
            for(int j=0;j<node[i].cnt;++j)
            {
                cin>>tmp;
                node[i].canbeat[j]=mp[tmp];
            }
        }
        memset(vis1,0,sizeof(vis1));
        memset(vis2,0,sizeof(vis2));
        finds=false;
        dfs(0);
        cout<<"Case "<<tcase<<": ";
        if(finds)
        {
            cout<<"Yes"<<endl;
            cout<<name[res[0]];
            for(int i=1;i<n;++i)
              cout<<" "<<name[res[i]];
            cout<<endl;
        }
        else cout<<"No"<<endl;
    }
    return 0;
}