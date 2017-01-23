#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<cmath>
#include<vector>
#include<queue>
#include<stack>
using namespace std;
typedef long long ll;
const int maxn=1000+10;
bool a[maxn][maxn],vis[maxn];
int links[maxn],n,head,fail,len;
void findchain(int u)
{
    for(int i=1;i<=n;++i)
    {
        if(vis[i]) continue;
        if(a[u][i])
        {
            links[i]=u;
            head=i;
            len++;
            vis[i]=true;
            findchain(i);
            break;
        }
    }
}
void solve()
{
    if(a[head][fail])
    {
        if(len==n) return ;
        for(int i=1;i<=n;++i)
        {
            if(!vis[i])
            {
                int u=head;
                while(!a[u][i]) u=links[u];
                if(u==fail)
                {
                    links[u]=i;
                }
                else
                {
                    links[fail]=head;
                    head=links[u];
                    links[u]=i;
                }
                fail=i;
                len++;
                vis[i]=true;
                break;
            }
        }
    }
    else
    {
        int u=links[head];
        while((!a[u][fail])||(!a[head][links[u]])) u=links[u];
        int v=links[u];
        int s=head,t=v;
        while(s!=v)
        {
            int tmp=links[s];
            links[s]=t;
            t=s;
            s=tmp;
        }
        head=u;
    }
    solve();
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    while(~scanf("%d",&n))
    {
        memset(vis,0,sizeof(vis));
        memset(a,0,sizeof(a));
        getchar();
        char at;
        for(int i=1;i<=n;++i)
        {
            int v;
            while(true)
            {
                at=getchar();
                if(at=='\n'||at==EOF) break;
                if(at>='0'&&at<='9')
                {
                    v=(at-'0');
                    while(true)
                    {
                        at=getchar();
                        if(at<'0'||at>'9')
                        {
                            a[i][v]=a[v][i]=true;
                            break;
                        }
                        v=v*10+(at-'0');
                    }
                }
                if(at=='\n'||at==EOF) break;
            }
        }
        vis[1]=true;
        head=1;fail=1;
        len=links[1]=1;
        findchain(1);
        solve();
        links[fail]=head;
        int u=links[1];
        printf("1");
        while(u!=1)
        {
            printf(" %d",u);
            u=links[u];
        }
        printf(" 1\n");
    }
    return 0;
}
