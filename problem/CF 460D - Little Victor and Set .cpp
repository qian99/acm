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
#include<assert.h>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    ll l,r,k;
    scanf("%I64d%I64d%I64d",&l,&r,&k);
    if(r - l + 1 > 4)
    {
        if(k >= 4)
        {
            printf("0\n");
            printf("4\n");
            if(l & 1) l++;
            for(int i = 0;i < 4;++i)
                printf("%I64d ",l + i);
            puts("");
        }
        else if(k == 2)
        {
            printf("1\n");
            printf("2\n");
            if(l & 1) l++;
            for(int i = 0;i < 2;++i)
                printf("%I64d ",l + i);
            puts("");
        }
        else if (k == 3)
        {
            ll bit = 0;
            for(int i = 40;i >=0;--i)
                if((1LL<<(ll)i) & l)
                {
                    bit = i;
                    break;
                }
            bit = (1LL<<(bit+1)) + (1LL<<bit);
            if(r>=bit)
            {
                printf("0\n");
                printf("3\n");
                printf("%I64d %I64d %I64d\n",l,bit,l^bit);
            }
            else
            {
                printf("1\n");
                printf("2\n");
                if(l & 1) l++;
                for(int i = 0;i < 2;++i)
                    printf("%I64d ",l + i);
                puts("");
            }
        }
        else
        {
            printf("%I64d\n",l);
            printf("1\n");
            printf("%I64d\n",l);
        }
    }
    else
    {
        int m = r - l + 1;
        ll minv = l;
        int minstate = 1,tot = 1;
        for(int i = 1;i < (1<<m);++i)
        {
            int cnt = 0;
            ll sum = 0;
            for(int j = 0;j < m;++j)
            {
                if(i & (1<<j))
                {
                    cnt++;
                    sum ^= (l + j);
                }
            }
            if(cnt <= k)
            {
                if(sum < minv)
                {
                    minv = sum;
                    minstate = i;
                    tot = cnt;
                }
            }
        }
        printf("%I64d\n",minv);
        printf("%d\n",tot);
        for(int i = 0;i < m;++i)
            if(minstate & (1<<i))
                printf("%I64d ",l+i);
        puts("");
    }
    return 0;
}