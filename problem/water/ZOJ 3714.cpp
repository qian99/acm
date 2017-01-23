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
const int maxn=10000+10;
int num[maxn];

int main()
{
    //freopen("in.txt","w",stdin);
    //freopen("out.txt","r",stdout);
    int t;
    cin>>t;
    int n,m;
    while(cin>>n>>m)
    {
        int a;
        for(int i=1;i<=n;++i)
        {
            cin>>a;
            num[i]=num[i+n]=a;
        }
        num[0]=0;
        int maxsum=0,sum=0;
        for(int i=1;i<=m;++i)
        {
            sum+=num[i];
        }
        int j=1;
        for(int i=m+1;i<=2*n;++i)
        {
            sum=sum-num[j]+num[i];
            maxsum=max(sum,maxsum);
            j++;
        }
        cout<<maxsum<<endl;
    }
    return 0;
}
