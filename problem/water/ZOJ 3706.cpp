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
const int maxn=200+10;
bool canmass[maxn];
int cal(int a,int b,int c)
{
    memset(canmass,false,sizeof canmass);
    canmass[a]=canmass[b]=canmass[c]=true;
    canmass[a+b]=canmass[b+c]=canmass[a+c]=true;
    canmass[a+b+c]=true;
    canmass[abs(a-b)]=canmass[abs(a-c)]=canmass[abs(b-c)]=true;
    canmass[abs(a+b-c)]=canmass[abs(a+c-b)]=canmass[abs(b+c-a)]=true;

    int ans=0;
    for(int i=1;i<=a+b+c;++i)
      if(canmass[i]) ans++;
    return ans;
}
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int a,b;
        cin>>a>>b;
        int maxnum=0;
        for(int i=1;i<a;++i)
        {
            maxnum=max(maxnum,cal(i,a-i,b));
        }
        for(int i=1;i<b;++i)
        {
            maxnum=max(maxnum,cal(i,b-i,a));
        }
        cout<<maxnum<<endl;
    }
    return 0;
}
