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
const int maxn=20;
//Y>X>2>A>K>Q>J>T>9>8>7>6>5>4>3
char str[maxn];
int cards[maxn],bomb,ocards[maxn],obomb,n,m;
int getval(char c)
{
    if(c >= '3' && c <= '9') return c - '0';
    if(c == 'T') return 10;
    if(c == 'J') return 11;
    if(c == 'Q') return 12;
    if(c == 'K') return 13;
    if(c == 'A') return 14;
    if(c == '2') return 15;
    if(c == 'X') return 16;
    return 17;
}
bool Solo()
{
    if(n == 1) return true;
    if(obomb != -1) return false;
    return cards[n-1] >= ocards[m-1];
}
bool Pair()
{
    if(n < 2) return false;
    int b1 = -1,b2 = -1;
    for(int i = 0;i <= n-2;++i)
    {
        if(cards[i] == cards[i+1])
            b1=cards[i];
    }
    if(b1 == -1) return false;
    if(n == 2) return true;
    if(obomb != -1) return false;
    for(int i = 0;i <= m-2;++i)
    {
        if(ocards[i] == ocards[i+1])
            b2 = ocards[i];
    }
    if(b2 == -1) return true;
    return b1 >= b2;
}
bool Trio()
{
    if(n < 3) return false;
    int b1 = -1,b2 = -1;
    for(int i = 0;i <= n-3;++i)
    {
        if(cards[i] == cards[i+1] &&cards[i] == cards[i+2])
            b1 = cards[i];
    }
    if(b1 == -1) return false;
    if(n == 3) return true;
    if(obomb != -1) return false;
    for(int i = 0;i <= m-3;++i)
    {
        if(ocards[i] == ocards[i+1] && ocards[i] == ocards[i+2])
            b2=ocards[i];
    }
    if(b2 == -1) return true;
    return b1 > b2;
}
bool Trio_Solo()
{
    if(n < 4) return false;
    int b1 = -1,b2 = -1;
    for(int i = 0;i <= n-3;++i)
    {
        if(cards[i] == cards[i+1] &&cards[i] == cards[i+2])
            b1 = cards[i];
    }
    if(b1 == -1) return false;
    if(n == 4) return true;
    if(obomb != -1) return false;
    for(int i = 0;i <= m-3;++i)
    {
        if(ocards[i] == ocards[i+1] && ocards[i] == ocards[i+2])
            b2=ocards[i];
    }
    if(b2 == -1 || m < 4) return true;
    return b1 > b2;
}
bool Trio_Pair()
{
    if(n < 5) return false;
    int b1 = -1,b2 = -1,c1 = -1,c2 = -1;
    for(int i = 0;i <= n-3;++i)
    {
        if(cards[i] == cards[i+1] &&cards[i] == cards[i+2])
            b1 = cards[i];
    }
    if(b1 == -1) return false;
    for(int i = 0;i <= n-2;++i)
    {
        if(cards[i] != b1 &&cards[i] == cards[i+1])
            c1 = cards[i];
    }
    if(c1 == -1) return false ;
    if(n == 5) return true;
    if(obomb != -1) return false;
    for(int i = 0;i <= m-3;++i)
    {
        if(ocards[i] == ocards[i+1] &&ocards[i] == ocards[i+2])
            b2 = ocards[i];
    }
    if(b2 == -1) return true;
    for(int i = 0;i <= m-2;++i)
    {
        if(ocards[i] != b2 &&ocards[i] == ocards[i+1])
            c2 = ocards[i];
    }
    if(c2 == -1) return true ;
    return b1 > b2;
}
bool Four_Dual()
{
    if(n < 6) return false;
    int b1 = -1,b2 = -1;
    for( int i = 0 ;i <= n-4;++i)
    {
        if(cards[i] == cards[i+1] && cards[i] == cards[i+2]
           && cards[i] == cards[i+3])
            b1=cards[i];
    }
    if(b1 == -1) return false;
    if(n == 6) return true;
    if(obomb != -1) return false;
    if(m < 6) return true;
    for(int i = 0;i <= m-4;++i)
    {
        if(ocards[i] == ocards[i+1] &&ocards[i] ==ocards[i+2]
           && ocards[i] == ocards[i+3])
            b2=cards[i];
    }
    if(b2 > b1) return false;
    return true;
}
bool solve()
{
    sort(cards , cards + n);
    sort(ocards , ocards + m);
    bomb = obomb =-1;
    for( int i = 0 ;i <= n-4;++i)
    {
        if(cards[i] == cards[i+1] && cards[i] == cards[i+2]
           && cards[i] == cards[i+3])
            bomb=cards[i];
    }
    if(n > 1 && cards[n-1]==17 && cards[n-2]==16)
        bomb = 17;
    for( int i = 0 ;i <= m-4;++i)
    {
        if(ocards[i] == ocards[i+1] && ocards[i] == ocards[i+2]
           && ocards[i] == ocards[i+3])
            obomb=ocards[i];
    }
    if(m > 1 && ocards[m-1]==17 && ocards[m-2]==16)
        obomb = 17;
    if(bomb > obomb) return true;
    if(bomb != -1 && n == 4) return true;
    if(Four_Dual()) return true;
    if(Trio_Pair()) return true;
    if(Trio_Solo()) return true;
    if(Trio()) return true;
    if(Pair()) return true;
    if(Solo()) return true;
    return false;
}
int main()
{
//    freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%s",str);
        n = strlen(str);
        for(int i = 0;i < n;++i)
            cards[i] = getval(str[i]);
        scanf("%s",str);
        m = strlen(str);
        for(int i = 0;i < m;++i)
            ocards[i] = getval(str[i]);
        if(solve()) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
