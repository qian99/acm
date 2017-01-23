char str[maxn],s[maxn<<1];
int p[maxn<<1];
int Manacher()
{
    int n=0;
    s[n++]='$';s[n++]='#';
    for(int i=0;str[i];i++)
    {
        s[n++]=str[i];
        s[n++]='#';
    }
    int mx=0,id=0,ans=0;
    p[0]=0;
    for(int i=1;i<n;++i)
    {
        p[i]=1;
        if(mx>i) p[i]=min(p[id*2-i],mx-i);
        while(s[i+p[i]]==s[i-p[i]]) p[i]++;
        if(i+p[i]>mx)
        {
            mx=i+p[i];
            id=i;
        }
        if(p[i]>ans) ans=p[i];
    }
    return ans-1;
}