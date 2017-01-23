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
const int maxn=300000+10;
int a[maxn],b[maxn],minv[maxn],maxv[maxn],ans[maxn];
ll sumone[maxn<<1],sumtwo[maxn<<1];
vector<pair<int,int> >one,two;
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,w;
    scanf("%d%d",&n,&w);
    for(int i=0;i<n;++i)
    {
        scanf("%d%d",&a[i],&b[i]);
        b[i]-=a[i];
        if(a[i]<=b[i])
        {
            one.push_back(make_pair(a[i],i));
            one.push_back(make_pair(b[i],i));
        }
        else
            two.push_back(make_pair(a[i]+b[i],i));
    }
    sort(one.begin(),one.end());
    sort(two.begin(),two.end());
    memset(ans,0,sizeof(ans));
    int size1=one.size();
    int size2=two.size();
    minv[size2]=inf;
    maxv[0]=0;
    for(int i=size2-1;i>=0;--i)
        minv[i]=min(minv[i+1],a[two[i].second]);
    for(int i=0;i<size2;++i)
        maxv[i+1]=max(maxv[i],b[two[i].second]);
    sumone[0]=sumtwo[0]=0;
    for(int i=0;i<size1;++i)
        sumone[i+1]=sumone[i]+one[i].first;
    for(int i=0;i<size2;++i)
        sumtwo[i+1]=sumtwo[i]+two[i].first;
    ll mintime=Inf,tmp;
    int sone,type;
    for(int i=0;i<=size1;++i)
    {
        tmp=sumone[i];
        if(w-i>=0&&w-i<=size2*2)
        {
            if((w-i)&1)
            {
                tmp+=sumtwo[(w-i)/2]+minv[(w-i)/2];
                type=0;
                if(sumone[i]+sumtwo[(w-i)/2]+two[(w-i)/2].first-maxv[(w-i)/2]<tmp)
                {
                    tmp=sumone[i]+sumtwo[(w-i)/2]+two[(w-i)/2].first-maxv[(w-i)/2];
                    type=1;
                }
            }
            else
                tmp+=sumtwo[(w-i)/2];
            if(tmp<mintime)
            {
                mintime=tmp;
                sone=i;
            }
        }
    }
    for(int i=0;i<sone;++i)
        ans[one[i].second]++;
    for(int j=0;j<(w-sone)/2;++j)
        ans[two[j].second]=2;
    if((w-sone)&1)
    {
        int mv=inf,pos;
        if(type==0)
        {
            for(int j=(w-sone)/2;j<size2;++j)
            {
                if(a[two[j].second]<mv)
                {
                    mv=a[two[j].second];
                    pos=two[j].second;
                }
            }
        }
        else
        {
            mv=-1;
            for(int j=0;j<(w-sone)/2;++j)
            {
                if(b[two[j].second]>mv)
                {
                    mv=b[two[j].second];
                    pos=two[j].second;
                }
            }
            ans[(w-sone)/2]=2;
        }
        ans[pos]=1;
    }
    printf("%I64d\n",mintime);
    for(int i=0;i<n;++i)
        printf("%d",ans[i]);
    printf("\n");
    return 0;
}
