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
const string res[5] = {"Apple","iPhone","iPod","iPad","Sony"};
const int to[5] = {0,0,0,0,1};
const string comment[2] = {"MAI MAI MAI!","SONY DAFA IS GOOD!"};
int main()
{
//    freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    string str;
    while(cin>>str)
    {
        int n = str.length(),m;
        bool flag;
        for(int i = 0;i < n;++i)
        {
            for(int j = 0;j < 5;++j)
            {
                m = res[j].length();
                if(i + m > n) continue;
                flag = true;
                for(int k = 0;k < m;++k)
                    if(str[i + k] != res[j][k])
                        flag = false;
                if(flag)
                    cout<<comment[to[j]]<<endl;
            }
        }
    }
    return 0;
}
