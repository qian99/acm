#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<set>
#include<cmath>
#include<vector>
#include<bitset>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
class SpecialStrings
{
    bool cal(string str)
    {
        int n = str.length();
        string s1,s2;
        for(int i = 1;i < n;++i)
        {
            s1 = str.substr(0,i);
            s2 = str.substr(i,n - i);
            if(s2 <= s1) return false;
        }
        return true;
    }
    string check(string str,int remain)
    {
        if(remain == 0)
        {
            if(cal(str))
                return str;
            return "";
        }
        string x = str;
        x += "0";
        for(int i = 0;i < remain - 1;++i)
            x += "1";
        if(cal(x))
        {
            str += "0";
            return check(str,remain - 1);
        }
        int n = x.length();
        x[n - remain] = '1';
        if(cal(x))
        {
            str += "1";
            return check(str,remain - 1);
        }
        return "";
    }
public:
    string findNext(string current)
    {
        int n = current.length();
        string ans = "",res,str;
        for(int i = n - 1;i >= 0;--i)
        {
            if(current[i] == '1') continue;
            str = "";
            for(int j = 0;j < i;++j)
                str += current[j];
            str += "1";
            res = check(str,n - i - 1);
            if(res.length() != 0)
            {
                ans = res;
                break;
            }
        }
        return ans;
    }
};