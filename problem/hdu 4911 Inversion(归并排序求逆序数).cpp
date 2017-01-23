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
const int maxn=100000+10;
int num[maxn],tmp[maxn];
ll MergeSort(int s,int t)
{
    if(s==t) return 0;
    ll sum=0;
    int m=(s+t)>>1;
    sum+=MergeSort(s,m);
    sum+=MergeSort(m+1,t);
    int i,k=m+1;
    for(i=s;i<=m;++i)
    {
        while(k<t&&num[i]>num[k]) k++;
        sum+=(k-(m+1))+(num[i]>num[k]?1:0);
    }
    i=0;
    int l=s,r=m+1;
    while(l<=m&&r<=t)
    {
        if(num[l]<num[r]) tmp[i++]=num[l++];
        else tmp[i++]=num[r++];
    }
    while(l<=m) tmp[i++]=num[l++];
    while(r<=m) tmp[i++]=num[r++];
    for(int j=0;j<i;++j) num[s+j]=tmp[j];
    return sum;
}
int main()
{
    //freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n,k;
    while(~scanf("%d%d",&n,&k))
    {
        for(int i=0;i<n;++i)
            scanf("%d",&num[i]);
        ll ans=MergeSort(0,n-1);
        ans-=k;
        ans=max(ans,0LL);
        printf("%I64d\n",ans);
    }
    return 0;
}