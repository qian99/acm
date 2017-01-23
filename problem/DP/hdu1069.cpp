#include <iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
const int maxn=1000+10;
struct Block
{
    int x,y,z;
};
Block blocks[maxn];
int dp[maxn];
void addblock(int p,int a,int b,int h)
{
    blocks[p].z=h;
    blocks[p].x=max(a,b);
    blocks[p].y=min(a,b);
}
bool cmp(Block a,Block b)
{
    if(a.x==b.x) return a.y>b.y;
    return a.x>b.x;
}
bool check(Block a,Block b)
{
    return a.x>b.x&&a.y>b.y;
}
int main()
{
    int t,n;
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    t=0;
    while(cin>>n)
    {
        if(n==0) break;
        t++;
        int ax,ay,az;
        int p=0;
        for(int i=0;i<n;++i)
        {
            cin>>ax>>ay>>az;
            addblock(p,ax,ay,az);
            p++;
            addblock(p,ax,az,ay);
            p++;
            addblock(p,ay,az,ax);
            p++;
        }
        sort(blocks,blocks+p,cmp);
        memset(dp,0,sizeof(dp));
        int maxsum=0;
        dp[0]=blocks[0].z;
        for(int i=1;i<p;++i)
        {
            dp[i]=blocks[i].z;
            for(int j=i-1;j>=0;--j)
            {
                if(check(blocks[j],blocks[i]))
                {
                    dp[i]=max(dp[i],dp[j]+blocks[i].z);
                }
                maxsum=max(dp[i],maxsum);
            }
        }
        cout<<"Case "<<t<<": maximum height = "<<maxsum<<endl;
    }
    return 0;
}
