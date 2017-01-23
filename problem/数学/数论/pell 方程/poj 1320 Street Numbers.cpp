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
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int xn=3,yn=1;
    for(int i=0;i<10;++i)
    {
        int tmp1=xn*3+8*yn;
        int tmp2=xn+yn*3;
        printf("%10d%10d\n",tmp2,(tmp1-1)/2);
        xn=tmp1;yn=tmp2;
    }
    return 0;
}
