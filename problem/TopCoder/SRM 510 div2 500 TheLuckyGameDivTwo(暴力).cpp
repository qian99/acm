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
class TheLuckyGameDivTwo
{
    public:
    int sum[5000];
    void Init()
    {
        sum[0]=0;
        for(int i=1;i<5000;++i)
        {
            int x=i,y;
            bool flag=true;
            while(x)
            {
                y=x%10;
                if(y!=4&&y!=7) {flag=false;break;}
                x/=10;
            }
            if(flag) sum[i]=sum[i-1]+1;
            else sum[i]=sum[i-1];
        }
    }
    int cal(int L,int R,int len)
    {
        int minv=inf;
        for(int i=L;i<=R-len+1;++i)
        {
            minv=min(sum[i+len-1]-sum[i-1],minv);
        }
        return minv;
    }
    int find(int a, int b, int jLen, int bLen)
    {
        Init();
        int maxv=-1;
        for(int i=a;i<=b-jLen+1;++i)
            maxv=max(maxv,cal(i,i+jLen-1,bLen));
        return maxv;
    }
};
//int main()
//{
//    //freopen("in.txt","r",stdin);
//    //freopen("out.txt","w",stdout);
//    TheLuckyGameDivTwo ans;
//    int a,b,c,d;
//    while(cin>>a>>b>>c>>d)
//    cout<<ans.find(a,b,c,d)<<endl;
//    return 0;
//}
