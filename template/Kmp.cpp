int find(char *T,char *P,int *f)
{
    int n=strlen(T),m=strlen(P);
    getFail(P,f);
    int j=0;
    for(int i=0;i<n;++i)
    {
        while(j&&T[i]!=P[j]) j=f[j];
        if(P[j]==T[i]) j++;
        if(j==m) printf("%d\n",i-m+1);
    }
}
void getFail(char *P,int *f)
{
    f[0]=f[1]=0;
    for(int i=1;i<n;++i)
    {
        int j=f[i];
        while(j>0&&P[i]!=P[j]) j=f[j];
        f[i+1]=P[i]==P[j]?j+1:0;
    }
}