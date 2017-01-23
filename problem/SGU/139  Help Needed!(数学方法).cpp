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
int num[20];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int cnt=0;
    for(int i=0;i<4;++i)
    {
        for(int j=0;j<4;++j)
        {
            scanf("%d",&num[i*4+j]);
            if(num[i*4+j]==0) num[i*4+j]=16,cnt=6-i+j;
        }
    }
    for(int i=1;i<16;++i)
      for(int j=0;j<i;++j)
        cnt+=num[i]<num[j]?1:0;
    if(cnt&1) printf("NO\n");
    else printf("YES\n");
    return 0;
}
