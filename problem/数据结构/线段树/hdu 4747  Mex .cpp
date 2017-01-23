#includeiostream
#includecstdio
#includecstring
#includestring
#includealgorithm
#includemap
#includequeue
#includestack
#includecmath
#includevector
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
using namespace std;
const int maxn=200000+10;
int num[maxn],head[maxn],a[maxn],next[maxn];
bool flag[maxn];
ll sum[maxn2],maxv[maxn2],minv[maxn2],setv[maxn2];
int n;
inline void PushUp(int rt)
{
    sum[rt]=sum[rt1]+sum[rt11];
    maxv[rt]=max(maxv[rt1],maxv[rt11]);
    minv[rt]=min(minv[rt1],minv[rt11]);
}
void PushDown(int l,int r,int rt)
{
    int ls=rt1,rs=rt11;
    int m=(l+r)1;
    if(setv[rt]=0)
    {
        setv[ls]=setv[rs]=setv[rt];
        sum[ls]=(m-l+1)setv[rt];
        sum[rs]=(r-m)setv[rt];
        maxv[ls]=maxv[rs]=setv[rt];
        minv[ls]=minv[rs]=setv[rt];
        setv[rt]=-1;
    }
}
void build(int l,int r,int rt)
{
    setv[rt]=-1;
    if(l==r)
    {
        sum[rt]=maxv[rt]=minv[rt]=num[l];
        return;
    }
    int m=(l+r)1;
    build(l,m,rt1);
    build(m+1,r,rt11);
    PushUp(rt);
}
void Update(int L,int R,int l,int r,int rt,int v)
{
    if(l=L&&r=R&&minv[rt]v)
    {
        setv[rt]=v;
        sum[rt]=(ll)(r-l+1)v;
        minv[rt]=maxv[rt]=v;
        return;
    }
    PushDown(l,r,rt);
    int m=(l+r)1;
    if(m=L&&maxv[rt1]v)
      Update(L,R,l,m,rt1,v);
    if(mR&&maxv[rt11]v)
      Update(L,R,m+1,r,rt11,v);
    PushUp(rt);
}
int main()
{
    freopen(in.txt,r,stdin);
    freopen(out.txt,w,stdout);
    while(~scanf(%d,&n))
    {
        if(n==0) break;
        memset(head,0xff,sizeof(head));
        memset(flag,0,sizeof(flag));
        int  nowv=0;
        for(int i=1;i=n;++i)
        {
            scanf(%d,&a[i]);
            if(a[i]n) a[i]=n+1;
            flag[a[i]]=true;
            if(a[i]==nowv)
            {
                while(flag[nowv]) nowv++;
            }
            num[i]=nowv;
        }
        for(int i=n;i0;--i)
        {
            next[i]=head[a[i]];
            head[a[i]]=i;
        }
        build(1,n,1);
        ll ans=sum[1];
        int r;
        for(int i=1;in;++i)
        {
            int p=head[a[i]];
            head[a[i]]=next[p];
            r=next[p];
            if(head[a[i]]!=-1) head[a[i]]=next[p];
            if(r==-1) r=n+1;
            if(i+1=r-1)
              Update(i+1,r-1,1,n,1,a[i]);
            Update(i,i,1,n,1,0);
            ans+=sum[1];
        }
        printf(%I64dn,ans);
    }
    return 0;
}
