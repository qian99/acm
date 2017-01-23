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
const int maxn=300+10;
int P[maxn],D[maxn];
int L,M,N;
double cal(double s)
{
    int l=0,r=0;
    double sum=0;
    for(int i=0;i<M;++i)
    {
        while(s+D[r]<=P[i]&&r<N-1) r++;
        l=max(0,r-1);
        sum+=min(abs(s+D[l]-P[i]),abs(s+D[r]-P[i]));
    }
    return sum;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%d%d",&L,&M);
    for(int i=0;i<M;++i)
        scanf("%d",&P[i]);
    scanf("%d",&N);
    D[0]=0;
    for(int i=1;i<N;++i)
        scanf("%d",&D[i]);
    double res=0,pos=0;
    for(double s=0;s<=L-D[N-1]+eps;s+=0.1)
    {
        double tmp=cal(s);
        if(tmp>res)
        {
            res=tmp;
            pos=s;
        }
    }
    printf("%lf %lf\n",pos,res);
    return 0;
}

