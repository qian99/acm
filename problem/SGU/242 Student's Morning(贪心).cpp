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
#include<bitset>
#include<set>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=200+10;
int cnt[maxn],flag[maxn],vis[maxn];
struct Node
{
    vector<int>vt;
    int val,exist;
    void getval(int x)
    {
        val=0;exist=0;
        for(int i=0;i<(int)vt.size();++i)
        {
            int y=vt[i];
            if(!flag[y]&&cnt[y]>1) val++;
            if(x==y) exist=1;
        }
    }
}node[maxn];
vector<pair<int,pair<int,int> > >ans;
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,k;
    scanf("%d%d",&n,&k);
    memset(cnt,0,sizeof(cnt));
    memset(flag,0,sizeof(flag));
    memset(vis,0,sizeof(vis));
    int tmp,m;
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&m);
        while(m--)
        {
            scanf("%d",&tmp);
            node[i].vt.push_back(tmp);
            cnt[tmp]++;
        }
    }
    cnt[0]=inf;
    bool can=true;
    int a[2],b[2];
    for(int i=0;i<k;++i)
    {
        int pos=0;
        for(int j=1;j<=k;++j)
            if(!flag[j]&&cnt[j]>=2&&cnt[pos]>cnt[j]) pos=j;
        if(!pos) {can=false;break;}
        flag[pos]=1;
        a[0]=a[1]=inf;
        for(int j=1;j<=n;++j)
            if(!vis[j])
            {
                node[j].getval(pos);
                if(node[j].exist)
                {
                    if(node[j].val<a[0])
                    {
                        a[1]=a[0];
                        b[1]=b[0];
                        a[0]=node[j].val;
                        b[0]=j;
                    }
                    else if(node[j].val<a[1])
                    {
                        a[1]=node[j].val;
                        b[1]=j;
                    }
                }
            }
        if(a[1]==inf) {can=false;break;}
        vis[b[0]]=vis[b[1]]=1;
        ans.push_back(make_pair(pos,make_pair(b[0],b[1])));
        for(int x=0;x<2;++x)
        for(int j=0;j<(int)node[b[x]].vt.size();++j)
        {
            int v=node[b[x]].vt[j];
            if(!flag[v]) cnt[v]--;
        }
    }
    if(!can) puts("NO");
    else
    {
        puts("YES");
        sort(ans.begin(),ans.end());
        pair<int,int>pii;
        for(int i=0;i<k;++i)
        {
            pii=ans[i].second;
            printf("2 %d %d\n",pii.first,pii.second);
        }
    }
    return 0;
}
