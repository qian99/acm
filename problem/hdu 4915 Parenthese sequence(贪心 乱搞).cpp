#pragma comment(linker, "/STACK:1024000000,1024000000")
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
const int maxn = 1000000+10;
char str[maxn];
int lx[maxn],rx[maxn],ly[maxn],ry[maxn];
bool check(int la, int ra,int lb,int rb)
{
    if(lb >= la && lb <= ra) return true;
    if(rb >= la && rb <= ra) return true;
    if(la <= lb && ra >= rb) return true;
    if(lb <= la && rb >= ra) return true;
    return false;
}
void solve()
{
    int n=strlen(str);
    if(str[0] == '?') str[0] = '(';
    if(str[n-1] == '?') str[n-1] = ')';
    int l=0,r=0;
    bool flag = true;
    for(int i = 0;i < n;++i)
    {
        if(str[i] == '(')
        {
            lx[i] = ++l;
            rx[i] = ++r;
        }
        else if(str[i] == ')')
        {
            lx[i] = --l;
            rx[i] = --r;
            if(r < 0) {flag = false; break;}
            if(l < 0) lx[i] = l = 1;
        }
        else
        {
            rx[i] = ++r;
            lx[i] = --l;
            if(l < 0) lx[i] = l = 1;
        }
    }
    if(!flag || l != 0)
    {
        printf("None\n");
        return ;
    }
    l = r =0;
    for(int i = n-1; i >=0 ;--i)
    {
        if(str[i] == '(')
        {
            ly[i] = ++l;
            ry[i] = ++r;
            if(l > 0) ly[i] = l = -1;
        }
        else if(str[i] == ')')
        {
            ly[i] = --l;
            ry[i] = --r;
        }
        else
        {
            ry[i] = --r;
            ly[i] = ++l;
            if(l > 0) ly[i] = l = -1;
        }
    }
    int la,ra,lb,rb;
    for(int i = 1;i < n-1; ++i)
    {
        if(str[i] == '?')
        {
            la = lx[i-1];
            ra = rx[i-1];
            lb = -ly[i+1];
            rb = -ry[i+1];
            if(check(la+1,ra+1,lb,rb)&&
               check(la-1,ra-1,lb,rb))
            {
                printf("Many\n");
                return ;
            }
        }
    }
    printf("Unique\n");
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w ",stdout);
    while(~scanf("%s",str))
    {
        solve();
    }
    return 0;
}
