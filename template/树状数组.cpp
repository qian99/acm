int lowbit(int x)
{
    return x&-x;
}
int sum(int x)
{
    int ret=0;
    while(x>0)
    {
        ret+=C[x];
        x-=lowbit(x);
    }
    return ret;
}
void add(int x,int v)
{
    while(x<N)
    {
        C[x]+=v;
        x+=lowbit(x);
    }
}