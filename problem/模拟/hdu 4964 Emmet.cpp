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
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 1000+10;
string str,S[maxn];
int cnt,n;
struct Node
{
    string head,end,context;
    void Uion(Node a)
    {
        context = a.head + a.context + a.end;
    }
};
Node cal(int L,int R)
{
    string name = "",id = "",cls = "";
    int s = L;
    while(s <=R && str[s] != '.' && str[s] != '#')
        name += str[s++];
    while(s <= R)
    {
        if(str[s] == '.')
        {
            s++;
            if(cls.length()) cls += " ";
            while(s <= R && str[s] != '.' && str[s] != '#')
                cls += str[s++];
        }
        else
        {
            s++;
            while(s <= R && str[s] != '.' && str[s] != '#')
                id += str[s++];
        }
    }
    Node res;
    res.head = "<" + name;
    if(id.length()) res.head += " id=\"" + id + "\"";
    if(cls.length()) res.head += " class=\"" + cls + "\"";
    res.head += ">";
    res.end = "</" + name + ">";
    return res;
}
int getmul(int L,int R,int & r)
{
    int mul = 1;
    for(int i = L;i <= R; ++i)
    {
        if(str[i] == '*')
        {
            mul = 0;
            for(int j = i + 1;j <= R; ++j)
                mul = mul*10 + str[j] - '0';
            r = i - 1;
        }
    }
    return mul;
}
Node getStr(int L,int R)
{
    Node res,node;
    if(L > R) return res;
    if(str[L] != '(')
    {
        int mul = 1,r = L;
        while(r <= R && str[r] != '>') r++;
        r--;
        mul = getmul(L,r,r);
        res = cal(L,r);
        while(r <= R && str[r] != '>') r++;
        node = getStr(r + 1,R);
        res.Uion(node);
        for(int i = 1;i < mul ;++i)
        {
            res.context += res.end + res.head + node.head +node.context +node.end;
        }
    }
    else
    {
        int sum = 0,last = L;
        string tmp = "";
        for(int i = L;i <= R;++i)
        {
            if(str[i] == '(') sum++;
            else if(str[i] == ')') sum--;
            if(sum == 0)
            {
                node = getStr(last + 1,i-1);
                last = i + 1;
                if(res.head.length() == 0)
                    res = node;
                else
                {
                    res.context += res.end + node.head + node.context;
                    res.end = node.end;
                }
            }
        }
    }
    return res;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t;
    cin>>t;
    while(t--)
    {
        cin>>str;
        n = str.length();
        cnt = 0;
        Node ans = getStr(0,n-1);
        cout<<ans.head<<ans.context<<ans.end<<endl;
    }
    return 0;
}