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
const int maxn=100000+10;
const int Lim=355;
vector<int>pt[maxn];
bool check(int x,int y)
{
    if(x>maxn||y>maxn) return false;
    return binary_search(pt[x].begin(),pt[x].end(),y);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,x,y;
    scanf("%d",&n);
    for(int i=0;i<n;++i)
    {
        scanf("%d%d",&x,&y);
        pt[x].push_back(y);
    }
    for(int i=0;i<maxn;++i)
        sort(pt[i].begin(),pt[i].end());
    int ans=0;
    for(int i=0;i<maxn;++i)
    {
        int size=pt[i].size();
        if(size<Lim)
        {
            for(int j=0;j<size;++j)
                for(int k=j+1;k<size;++k)
                {
                    int d=pt[i][k]-pt[i][j];
                    if(d&&check(i+d,pt[i][k])&&check(i+d,pt[i][j]))
                        ans++;
                }
        }
        else
        {
            for(int j=i+1;j<maxn;++j)
            {
                int sz=pt[j].size();
                int d=j-i;
                if(d)
                for(int k=0;k<sz;++k)
                {
                    if(check(i,pt[j][k])&&check(i,pt[j][k]+d)&&check(j,pt[j][k]+d))
                        ans++;
                }
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}
