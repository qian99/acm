void RMQ_init(int n)
{
    for(int i=1;i<=n;++i) d[i][0]=value[i];
    for(int j=1;(1<<j)<=n;++j)
    {
        for(int i=1;i+(1<<j)-1<=n;++i)
        {
            d[i][j]=max(d[i][j-1],d[i+(1<<(j-1))][j-1]);
        }
    }
}
int RMQ(int L,int R)
{
    //if(R<L) return 0;
    int k=0;
    while((1<<(k+1))<=R-L+1) k++;
    return max(d[L][k],d[R-(1<<k)+1][k]);
}