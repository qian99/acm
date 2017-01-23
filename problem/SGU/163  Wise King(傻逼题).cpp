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
int main()
{

    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,p,tmp;
    int a[5]={0},b[5]={0};
    ll sum=0;
    cin>>n>>p;
    for(int i=0;i<n;++i)
    {
        scanf("%d",&tmp);
        if(tmp>0) a[tmp]++;
        else b[-tmp]++;
    }
    for(int i=1;i<=3;++i)
    {
        tmp=1;
        for(int j=0;j<p;++j)
          tmp*=i;
        sum+=tmp*a[i];
    }
    if(p%2==0)
    {
        for(int i=1;i<=3;++i)
        {
            tmp=1;
            for(int j=0;j<p;++j)
              tmp*=i;
            sum+=tmp*b[i];
        }
    }
    cout<<sum<<endl;
    return 0;
}

