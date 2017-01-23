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
int add[6]={1,1,3,1,1,4};
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int k;
    cin>>k;
    if(k==1)
    {
        cout<<8<<endl;
    }
    else
    {
        k--;
        k=k%6;
        if(k==0) k=6;
        cout<<add[k-1]<<endl;
    }
    return 0;
}
