#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
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
char a[maxn],b[maxn];
bool flag[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%s",a);
    scanf("%s",b);
    memset(flag,0,sizeof(flag));
    int n=strlen(a);
    int m=strlen(b);
    if(n!=m) {printf("-1\n");}
    else
    {
        bool ca=true;
        int zs=0,fs=0;
        int cnt=0,now=0,znt=0,fnt=0;
        while(a[zs]!='+'&&zs<n) zs++;
        while(a[fs]!='-'&&fs<n) fs++;
        for(int i=0;i<n;++i)
        {
            if(a[now]==b[i])
            {
                if(now==zs)
                {
                    while(true)
                    {
                        zs++;
                        if(flag[zs]) {znt++;continue;}
                        if(zs==n||a[zs]=='+') break;
                    }
                }
                if(now==fs)
                {
                    while(true)
                    {
                        fs++;
                        if(flag[fs]) {fnt++;continue;}
                        if(fs==n||a[fs]=='-') break;
                    }
                }
                now++;
                while(flag[now]&&now<n) now++,znt--,fnt--;
            }
            else
            {
                if(b[i]=='+')
                {
                    if(zs==n) {ca=false;break;}
                    cnt+=zs-now-znt;
                    flag[zs]=true;
                    znt++;
                    if(zs<fs) fnt++;
                    while(true)
                    {
                        zs++;
                        if(flag[zs]) {znt++;continue;}
                        if(zs==n||a[zs]=='+') break;
                    }
                }
                else
                {
                    if(fs==n) {ca=false;break;}
                    cnt+=fs-now-fnt;
                    flag[fs]=true;
                    fnt++;
                    if(fs<zs) znt++;
                    while(true)
                    {
                        fs++;
                        if(flag[fs]) {fnt++;continue;}
                        if(fs==n||a[fs]=='-') break;
                    }
                }
            }
        }
        if(!ca) printf("-1\n");
        else printf("%d\n",cnt);
    }
    return 0;
}
