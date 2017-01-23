const int lev=15;
int ch[maxm][2],sum[maxm],size;
int root[maxn];
int Newnode(int val)
{
   size++;
   ch[size][0]=ch[size][1]=0;
   sum[size]=val;
   return size;
}
int Insert(int x,int val,int dep)
{
    int rt=Newnode(sum[x]+1);
    if(dep==-1) return rt;
    int d=(val>>dep)&1;
    ch[rt][d^1]=ch[x][d^1];
    ch[rt][d]=Insert(ch[x][d],val,dep-1);
    return rt;
}
int query(int x,int y,int val)
{
    int res=0;
    for(int i=lev;i>=0;--i)
    {
        int d=(val>>i)&1;
        int tmp=sum[ch[y][d^1]]-sum[ch[x][d^1]];
        if(tmp>0) res|=(1<<i);
        else d^=1;
        x=ch[x][d^1];y=ch[y][d^1];
    }
    return res;
}