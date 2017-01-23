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
#include<bitset>
#include<set>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=100+10;
const int maxm=10000+10;
int a[maxn];
char str[maxm];
void flip(int pos,int n)
{
    for(int i=0;i<n;++i)
    {
        if(i+1>=pos-i) break;
        swap(a[i+1],a[pos-i]);
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n=0;
    while(gets(str))
    {
        int len=strlen(str);
        if(len==0) continue;
        memset(a,0,sizeof(a));
        bool flag=true;
        n=0;
        for(int i=0;i<len;++i)
        {
            if(str[i]>='0'&&str[i]<='9')
            {
                if(flag) n++;
                flag=false;
                a[n]=a[n]*10+(str[i]-'0');
            }
            else flag=true;
        }
        printf("%d",a[1]);
        for(int i=2;i<=n;++i)
            printf(" %d",a[i]);
        printf("\n");
        for(int i=n;i>=1;--i)
        {
            int maxv=-1000,pos;
            for(int j=i;j>=1;--j)
                if(maxv<a[j]) {maxv=a[j];pos=j;}
            if(pos==i) continue;
            flip(pos,n);
            flip(i,n);
            printf("%d %d ",n-pos+1,n-i+1);
        }
        printf("0\n");
    }
    return 0;
}
