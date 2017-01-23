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
const int maxn=5000+10;
char str[maxn];
int addr[5];
void printchar(char c)
{
    int v=(int)c;
    int a=v%16;
    v/=16;
    int b=v%16;
    if(b<10) printf("%d",b);
    else printf("%c",b-10+'a');
    if(a<10) printf("%d",a);
    else printf("%c",a-10+'a');
}
void printcov(char c)
{
    if(c>='a'&&c<='z')
      printf("%c",c-'a'+'A');
    else if(c>='A'&&c<='Z')
      printf("%c",c-'A'+'a');
    else printf("%c",c);
}
void addad()
{
    addr[1]++;
    int i=1;
    while(addr[i]==16)
    {
        addr[i]=0;
        i++;
        addr[i]++;
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(gets(str))
    {
        memset(addr,0,sizeof(addr));
        int n=strlen(str);
        int s=0;
        while(s<n)
        {
            for(int i=3;i>=0;--i)
            {
                if(addr[i]<10) printf("%d",addr[i]);
                else printf("%c",addr[i]-10+'a');
            }
            printf(": ");
            for(int i=0;i<16;i+=2)
            {
                if(i+s<n) printchar(str[i+s]);
                else printf("  ");
                if(i+s+1<n) printchar(str[i+s+1]);
                else printf("  ");
                printf(" ");
            }
            for(int i=s;i<s+16;i++)
                if(i<n) printcov(str[i]);
            printf("\n");
            addad();
            s+=16;
        }
    }
    return 0;
}
