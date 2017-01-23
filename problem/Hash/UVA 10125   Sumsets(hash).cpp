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
const int maxn=1000+10;
struct Node
{
    int a,b;
    Node(){};
    Node(int aa,int bb) {a=aa;b=bb;}
};
int num[maxn];
vector<Node>sum[maxn*maxn];
bool check(int id,int i,int j)
{
    for(int k=0;k<(int)sum[id].size();++k)
    {
        if(sum[id][k].a!=i&&sum[id][k].a!=j&&sum[id][k].b!=i&&sum[id][k].b!=j)
            return true;
    }
    return false;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m=0;
    map<int,int>mp;
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        for(int i=0;i<=m;++i) sum[i].clear();
        mp.clear();
        for(int i=0;i<n;++i)
            scanf("%d",&num[i]);
        int tmp,id;
        for(int i=0;i<n;++i)
            for(int j=i+1;j<n;++j)
            {
                tmp=num[i]+num[j];
                id=mp[tmp];
                if(!id) {mp[tmp]=++m;id=m;}
                sum[id].push_back(Node(i,j));
            }
        bool flag=false;
        int maxd=-inf;
        for(int i=0;i<n;++i)
            for(int j=i+1;j<n;++j)
            {
                if(!(flag&&num[i]<=maxd))
                {
                    tmp=num[i]-num[j];
                    id=mp[tmp];
                    if(id&&check(id,i,j))
                    {
                        flag=true;
                        if(num[i]>maxd) maxd=num[i];
                    }
                }
                if(!(flag&&num[j]<=maxd))
                {
                    tmp=num[j]-num[i];
                    id=mp[tmp];
                    if(id&&check(id,j,i))
                    {
                        flag=true;
                        if(num[j]>maxd) maxd=num[j];
                    }
                }
            }
        if(flag) printf("%d\n",maxd);
        else printf("no solution\n");
    }
    return 0;
}

