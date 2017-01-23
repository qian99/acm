#include <iostream>
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
const int maxn=50+10;
int num[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(cin>>n>>m)
    {
        for(int i=0;i<m;++i)
          cin>>num[i];
        sort(num,num+m);
        int minv=inf;
        for(int i=0;i<m-n+1;++i)
            minv=min(minv,num[i+n-1]-num[i]);
        cout<<minv<<endl;
    }
    return 0;
}