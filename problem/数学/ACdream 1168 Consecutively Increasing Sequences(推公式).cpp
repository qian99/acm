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
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int SIZE = 7;
const int mod = 1000000000;
struct bignum
{
    long long a[SIZE];
    bignum() {
        memset(a,0,sizeof(a));
    }

    bignum(long long n) {
        memset(a,0,sizeof(a));
        a[0] = n;
        adjust();
    }

    void adjust() {
        for(int i = 0; i < SIZE; i ++)
            if(a[i] >= mod) {
                a[i + 1] += a[i] / mod;
                a[i] %= mod;
            }
            else if(a[i] < 0) {
                a[i + 1] --;
                a[i] += mod;
            }
    }

    bignum operator * (const bignum &p) {
        bignum c;
        for(int i = 0; i < SIZE; i ++)
            for(int j = 0; i + j < SIZE; j ++)
                c.a[i + j] += a[i] * p.a[j];
        c.adjust();
        return c;
    }

    bignum operator / (const int x) {
        long long tmp = 0;
        bignum c;
        memcpy(c.a,a,sizeof(a));
        for(int i = SIZE - 1; i >= 0; i --) {
            long long p = (tmp * mod + c.a[i]) % x;
            c.a[i] = (tmp * mod + c.a[i]) / x;
            tmp = p;
        }
        return c;
    }

    bignum operator + (bignum &p) {
        bignum c;
        for(int i = 0; i < SIZE; i ++)
            c.a[i] = a[i] + p.a[i];
        c.adjust();
        return c;
    }

    bignum operator - (bignum &p) {
        bignum c;
        for(int i = 0; i < SIZE; i ++)
            c.a[i] = a[i] - p.a[i];
        c.adjust();
        return c;
    }

    bool operator == (bignum &p) {
        for(int i = 0; i < SIZE; i ++)
            if(a[i] != p.a[i]) return false;
        return true;
    }

    void output() {
        int i = SIZE - 1;
        for(i; i >= 0; i --) {
            if(a[i]) break;
        }
        printf("%lld",a[i]);
        for(i = i - 1; i >= 0; i --)
            printf("%09lld",a[i]);
        printf("\n");
    }
};
bignum cal1(int n)
{
    return bignum(n)*bignum(n+1)/2;
}
bignum cal2(int n)
{
    return bignum(n)*bignum(n+1)*bignum(2*n+1)/6;
}
bignum cal3(int n)
{
    return cal1(n)*cal1(n);
}
bignum cal(int n)
{
    bignum x=cal3(n);
    bignum y=bignum(2)*cal3(n);
    bignum z=bignum(3)*cal2(n);
    bignum p=cal1(n);
    y=y-z+p;
    y=y/6;
    x=x-y;
    return x;
}
void solve(int n)
{
    bignum res=bignum(0);
    int m;
    for(int i=0;i<100;++i)
    {
        m=min(n,1<<i);
        n-=m;
        bignum tmp=cal(m);
        res=res+tmp;
        if(n==0) break;
    }
    res.output();
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        solve(n);
    }
    return 0;
}
