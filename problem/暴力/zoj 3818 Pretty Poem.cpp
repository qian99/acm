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
const int maxn = 100 + 10;
char str[maxn],A[maxn],B[maxn],C[maxn],lenA,lenB,lenC,n;
bool check(char * s1,char * s2,int x,int y,int len)
{
    for(int i = 0;i < len;++i)
    {
        if(s1[x + i] != s2[y + i])
            return false;
    }
    return true;
}
bool check1()
{
    if(lenA*3 + lenB*2 != n) return false;
    if(!check(str,A,0,0,lenA)) return false;
    if(!check(str,A,lenA + lenB,0,lenA)) return false;
    if(!check(str,A,lenA*2 + lenB*2,0,lenA)) return false;
    if(!check(str,B,lenA,0,lenB)) return false;
    if(!check(str,B,lenA*2 + lenB,0,lenB)) return false;
    return true;
}
bool check2()
{
    if(lenA*3 + lenB*3 + lenC != n) return false;
    if(!check(str,A,0,0,lenA)) return false;
    if(!check(str,A,lenA + lenB,0,lenA)) return false;
    if(!check(str,A,lenA*2 + lenB*2 + lenC,0,lenA)) return false;

    if(!check(str,B,lenA,0,lenB)) return false;
    if(!check(str,B,lenA*2 + lenB,0,lenB)) return false;
    if(!check(str,B,lenA*3 + lenB*2 + lenC,0,lenB)) return false;

    if(!check(str,C,lenA*2 + lenB*2,0,lenC)) return false;
    return true;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%s",str);
        n = strlen(str);
        int N = 0;
        for(int i = 0;i < n;++i)
            if((str[i] >= 'A' && str[i] <= 'Z')||(str[i]>='a' && str[i] <= 'z'))
                str[N++] = str[i];
        n = N;
        bool flag = false;
        for(int i = 1;i <= n && !flag;++i)
        {
            for(int j = 1;i + j <= n && !flag;++j)
            {
                lenA = i;
                lenB = j;
                for(int x = 0;x < lenA;++x)
                    A[x] = str[x];
                for(int x = 0;x < lenB;++x)
                    B[x] = str[x + lenA];
                if(lenA == lenB && check(A,B,0,0,lenA)) continue;
                if(check1()) flag = true;
                for(int k = 1; i*3 + j*3 + k <= n && !flag;++k)
                {
                    lenC = k;
                    for(int x = 0;x < lenC;++x)
                        C[x] = str[x + lenA*2 + lenB*2];
                    if(lenA == lenC && check(A,C,0,0,lenA)) continue;
                    if(lenB == lenC && check(B,C,0,0,lenC)) continue;
                    if(check2()) flag = true;
                }
            }
        }
        if(flag) puts("Yes");
        else puts("No");
    }
    return 0;
}