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
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=1000+10;
char s[maxn];
struct BigNum
{
    int num[550],len;
    void clear() {memset(num,0,sizeof(num));len=0;}
    void Init(const char * str)
    {
        len=strlen(str);
        for(int i=0;i<len;++i)
            num[i]=str[i]-'0';
        reverse(num,num+len);
    }
    void ptnum()
    {
        for(int i=len-1;i>=0;--i)
            printf("%d",num[i]);
    }
}bg[maxn];
BigNum operator + (const BigNum a,const BigNum b)
{
    BigNum c;c.clear();
    c.len=max(a.len,b.len);
    for(int i=0;i<c.len;++i)
    {
        c.num[i]+=a.num[i]+b.num[i];
        if(c.num[i]>9) c.num[i+1]+=c.num[i]/10,c.num[i]%=10;
    }
    while(c.num[c.len])
    {
        if(c.num[c.len]>9) c.num[c.len+1]+=c.num[c.len]/10,c.num[c.len]%=10;
        c.len++;
    }
    return c;
}
bool operator <(const BigNum a,const BigNum b)
{
    if(a.len!=b.len) return a.len<b.len;
    for(int i=a.len-1;i>=0;--i)
        if(a.num[i]!=b.num[i]) return a.num[i]<b.num[i];
    return false;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;++i)
    {
        scanf("%s",s);
        bg[i].Init(s);
    }
    sort(bg,bg+n);
    bool flag=false;
    for(int i=2;i<n;++i)
    {
//        BigNum tmp=bg[i-1]+bg[i-2];
        if(bg[i]<bg[i-1]+bg[i-2])
        {
            bg[i-2].ptnum();
            printf(" ");
            bg[i-1].ptnum();
            printf(" ");
            bg[i].ptnum();
            flag=true;
            break;
        }
    }
    if(!flag)
        puts("0 0 0\n");
    return 0;
}
