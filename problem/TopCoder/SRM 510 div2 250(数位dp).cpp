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
class TheAlmostLuckyNumbersDivTwo
{
    public:
    int dp[15][4],num[15];
    int f(int pos,int st,bool limit)
    {
        if(pos==-1) return 1;
        if(dp[pos][st]!=-1&&!limit) return dp[pos][st];
        int res=0;
        int last=limit?num[pos]:9;
        for(int i=0;i<=last;++i)
        {
            if(i==0&&(!(st&2))) res+=f(pos-1,st,limit&&i==last);
            else if(i==4||i==7) res+=f(pos-1,st|2,limit&&i==last);
            else if(st&1) continue;
            else res+=f(pos-1,st|3,limit&&i==last);
        }
        if(!limit) dp[pos][st]=res;
        return res;
    }
    int cal(int x)
    {
        int len=0;
        while(x)
        {
            num[len++]=x%10;
            x/=10;
        }
        return f(len-1,0,true);
    }
    int find(int a,int b)
    {
        memset(dp,0xff,sizeof(dp));
        return cal(b)-cal(a-1);
    }
};
//int main()
//{
//    //freopen("in.txt","r",stdin);
//    //freopen("out.txt","w",stdout);
//    TheAlmostLuckyNumbersDivTwo ans;
//    int a,b;
//    cin>>a>>b;
//    cout<<ans.find(a,b)<<endl;
//    return 0;
//}
