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
const int maxn=100+10;
int num[maxn][maxn];
int main()
{
    int t,n;
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    cin>>t;
    while(t--)
    {
        cin>>n;
        memset(num,0,sizeof(num));
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=i;++j)
            {
                cin>>num[i][j];
            }
        }
        for(int i=n-1;i>=1;--i)
        {
            for(int j=1;j<=i;++j)
            {
                num[i][j]+=max(num[i+1][j],num[i+1][j+1]);
            }
        }
        cout<<num[1][1]<<endl;
    }
    return 0;
}
