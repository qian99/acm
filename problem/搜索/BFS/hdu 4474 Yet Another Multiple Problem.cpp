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
const int maxn=10000+10;
bool flag[15];
bool vis[maxn];
int n,m;
struct Node
{
    string res;
    int v;
};
queue<Node>q;
void bfs()
{
    while(!q.empty()) q.pop();
    Node node,tn;
    char str[2];str[1]='\0';
    for(int i=1;i<=9;++i)
    {
        if(!flag[i])
        {
            vis[i%n]=true;
            if(i%n==0)
            {
                cout<<i<<endl;
                return ;
            }
            node.v=i%n;
            str[0]=i+'0';
            node.res=str;
            q.push(node);
        }
    }
    while(!q.empty())
    {
        node=q.front();q.pop();
        for(int i=0;i<=9;++i)
        {
            if(!flag[i])
            {
                int tmp=(node.v*10+i)%n;
                if(tmp==0)
                {
                    cout<<node.res<<i<<endl;
                    return ;
                }
                if(!vis[tmp])
                {
                    tn.v=tmp;
                    str[0]=i+'0';
                    tn.res=node.res+str;
                    vis[tmp]=true;
                    q.push(tn);
                }
            }
        }
    }
    cout<<"-1"<<endl;
    return;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int tcase=0;
    while(~scanf("%d%d",&n,&m))
    {
        tcase++;
        memset(flag,0,sizeof(flag));
        memset(vis,0,sizeof(vis));
        int tmp;
        for(int i=0;i<m;++i)
        {
            scanf("%d",&tmp);
            flag[tmp]=true;
        }
        printf("Case %d: ",tcase);
        bfs();
    }
    return 0;
}
