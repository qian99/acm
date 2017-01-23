//求n的欧拉函数
int euler_phi(int n)
{
    int m=sqrt(n+0.5);
    int ans=n;
    for(int i=2;i<=m;++i)
    {
        if(n%i==0)
        {
            ans=ans-ans/i;
            while(n%i==0) n/=i;
        }
    }
    if(n>1) ans=ans-ans/n;
    return ans;
}


//筛法求欧拉函数
void phi_table()
{
    phi[1]=0;
    for(int i=2;i<maxn;++i) phi[i]=i;
    for(int i=2;i<maxn;++i)
    {
        if(phi[i]==i)
        {
            phi[i]=i-1;
            for(int j=i*2;j<maxn;j+=i)
                phi[j]=phi[j]-phi[j]/i;
        }
    }
}