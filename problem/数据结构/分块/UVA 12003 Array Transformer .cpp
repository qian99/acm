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
const int maxn=300000+100;
const int Size=550;
int block[Size+10][Size+10];
int A[maxn];
void Init(int n)
{
    int now=0,j=0;
    for(int i=0;i<n;++i)
    {
        scanf("%d",&A[i]);
        block[now][j]=A[i];
        j++;
        if(j==Size) {now++,j=0;}
    }
    for(int i=0;i<now;++i) sort(block[i],block[i]+Size);
    if(j) sort(block[now],block[now]+j);
}
int f(int p,int v)
{
    int l=0,r=Size-1,m;
    if(block[p][r]<v) return r+1;
    while(l<r)
    {
        m=(l+r)>>1;
        if(block[p][m]<v)
            l=m+1;
        else
            r=m;
    }
    return l;
}
int getval(int L,int R,int v)
{
    int cnt=0;
    int la=L/Size,ra=R/Size;
    if(la==ra)
    {
        for(int i=L;i<=R;++i)
            if(A[i]<v) cnt++;
    }
    else
    {
        for(int i=L;i<(la+1)*Size;++i)
            if(A[i]<v) cnt++;
        for(int i=ra*Size;i<=R;++i)
            if(A[i]<v) cnt++;
        for(int i=la+1;i<ra;++i)
            cnt+=f(i,v);
    }
    return cnt;
}
void changes(int p,int x)
{
    if(A[p]==x) return ;
    int old=A[p],pos=0,rp=p/Size;
    A[p]=x;
    while(block[rp][pos]<old) pos++;
    block[rp][pos]=x;
    if(x>old) while(pos<Size-1&&block[rp][pos]>block[rp][pos+1])
        swap(block[rp][pos],block[rp][pos+1]),pos++;
    else    while(pos>0&&block[rp][pos]<block[rp][pos-1])
        swap(block[rp][pos],block[rp][pos-1]),pos--;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m,u;
    while(~scanf("%d%d%d",&n,&m,&u))
    {
        Init(n);
        int L,R,v,p;
        while(m--)
        {
            scanf("%d%d%d%d",&L,&R,&v,&p);
            L--;R--;p--;
            int k=getval(L,R,v);
            changes(p,(ll)u*k/(R-L+1));
        }
        for(int i=0;i<n;++i)
            printf("%d\n",A[i]);
    }
    return 0;
}
