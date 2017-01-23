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
const int maxn=100000+10;
bool flag[maxn<<1],visx[maxn<<1],visy[maxn<<1];
vector<int>xnode[maxn<<1];
vector<int>ynode[maxn<<1];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    map<ll,int>mp;
    while(~scanf("%d%d",&n,&m))
    {
        if(n==0&&m==0) break;
        memset(flag,0,sizeof(flag));
        memset(visx,0,sizeof(visx));
        memset(visy,0,sizeof(visy));
        for(int i=0;i<maxn*2;++i)
        {
            xnode[i].clear();
            ynode[i].clear();
        }
        mp.clear();
        ll px,py;
        int z=1,a,b;
        for(int i=1;i<=n;++i)
        {
            scanf("%I64d%I64d",&px,&py);
            if(!mp[px]) mp[px]=z++;
            if(!mp[py]) mp[py]=z++;
            a=mp[px],b=mp[py];
            xnode[a].push_back(i);
            ynode[b].push_back(i);
        }
        while(m--)
        {
            scanf("%d%I64d",&a,&px);
            if(!mp[px])
            {
                printf("0\n");
                continue;
            }
            b=mp[px];
            int ans=0;
            if(a==0)
            {
                if(!visx[b])
                {
                    visx[b]=true;
                    for(int i=0;i<xnode[b].size();++i)
                    {
                        int tmp=xnode[b][i];
                        if(!flag[tmp])
                        {
                            flag[tmp]=true;
                            ans++;
                        }
                    }
                }
            }
            else
            {
                if(!visy[b])
                {
                    visy[b]=true;
                    for(int i=0;i<ynode[b].size();++i)
                    {
                        int tmp=ynode[b][i];
                        if(!flag[tmp])
                        {
                            flag[tmp]=true;
                            ans++;
                        }
                    }
                }

            }
            printf("%d\n",ans);
        }
        printf("\n");
    }
    return 0;
}
