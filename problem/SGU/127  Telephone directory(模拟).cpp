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
const int maxn=8000+10;
int num[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int k,n;
    while(cin>>k)
    {
        cin>>n;
        for(int i=0;i<n;++i)
          cin>>num[i];
        sort(num,num+n);
        int page=2,last=0,cnt=0;
        for(int i=0;i<n;++i)
        {
            if(last==num[i]/1000&&cnt<k)
              cnt++;
            else
            {
                page++;
                last=num[i]/1000;
                cnt=1;
            }
        }
        cout<<page<<endl;
    }
    return 0;
}
