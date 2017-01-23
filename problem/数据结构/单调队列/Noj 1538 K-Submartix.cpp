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
const int maxn=250+10;
ll suml[maxn][maxn],sumr[maxn],val[maxn],nval;
int pos[maxn],m,n,head,fail,k,minlen,ans,np;
void solve(int l,int r)
{
    minlen=inf;
    head=fail=0;
    sumr[0]=0;
    for(int i=1;i<=m;++i)
        sumr[i]=sumr[i-1]+suml[i][r]-suml[i][l-1];
    val[0]=0;pos[fail++]=0;
    for(int i=1;i<=m;++i)
    {
        nval=sumr[i];np=i;
        while((fail>head+1)&&(nval-val[head+1]>=k)) head++;
        if(nval-val[head]>=k)
        {
            int len=np-pos[head];
            if(len<minlen) minlen=len;
        }
        while(fail>head&&val[fail-1]>=nval) fail--;
        val[fail]=nval;pos[fail++]=np;
    }
    if(minlen!=inf) ans=min(ans,minlen*(r-l+1));
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d%d",&m,&n,&k))
    {
        int num;
        for(int i=1;i<=m;++i)
        {
            suml[i][0]=0;
            for(int j=1;j<=n;++j)
            {
                scanf("%d",&num);
                suml[i][j]=suml[i][j-1]+num;
            }
        }
        ans=inf;
        for(int i=1;i<=n;++i)
            for(int j=i;j<=n;++j)
                if(j-i+1<ans) solve(i,j);
        if(ans==inf) ans=-1;
        printf("%d\n",ans);
    }
    return 0;
}

