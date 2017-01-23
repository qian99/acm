const int SIZE = 70;
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