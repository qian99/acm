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
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
const int maxn=100000+10;
int num[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    num[0]=0;
    double tmp;
    memset(num,0,sizeof(num));
    int i=1;
    while(i*i<=100000)
    {
        num[i*i]=1;
        i++;
    }
    for(int j=1;j<=100000;++j)
      num[j]+=num[j-1];
    int a,b;
    while(cin>>a>>b)
    {
        if(a==0&&b==0) break;
        cout<<num[b]-num[a-1]<<endl;
    }
    return 0;
}
