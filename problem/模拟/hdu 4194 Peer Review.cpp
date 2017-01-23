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
const int maxn=1000+10;
int id[maxn],degree[maxn];
vector<int>lists[maxn];
char str[20];
map<string,int>mp;
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d%d",&m,&n))
    {
        if(m==0&&n==0) break;
        mp.clear();
        memset(degree,0,sizeof(degree));
        int tot=0,x;
        for(int i=0;i<=n;++i) lists[i].clear();
        for(int i=1;i<=n;++i)
        {
            scanf("%s",str);
            if(!mp[(string)str]) id[i]=mp[(string)str]=++tot;
            else id[i]=mp[(string)str];
            for(int j=0;j<m;++j)
            {
                scanf("%d",&x);
                lists[x].push_back(i);
                degree[x]++;
            }
        }
        int ans=0;
        for(int i=1;i<=n;++i)
        {
            if(degree[i]!=m) ans++;
            else
            {
                sort(lists[i].begin(),lists[i].end());
                for(int j=0;j<(int)lists[i].size();++j)
                {
                    x=lists[i][j];
                    if(id[i]==id[x]) {ans++;break;}
                    if(j&&x==lists[i][j-1]) {ans++;break;}
                }
            }
        }
        if(ans) printf("%d PROBLEMS FOUND\n",ans);
        else if(ans==1) printf("1 PROBLEM FOUND\n");
        else printf("NO PROBLEMS FOUND\n");
    }
    return 0;
}
