void getprimes()
{
    memset(flag,0,sizeof(flag));
    pcnt = 0;
    for(int i = 2;i < maxm;++i)
    {
        if(!flag[i])
        {
            primes[pcnt++] = i;
            min_div[i] = i;
        }
        for(int j = 0;j < pcnt;++j)
        {
            if(i*primes[j] > maxm) break;
            flag[i*primes[j]] = true;
            min_div[i*primes[j]] = primes[j];
            if(i % primes[j] == 0) break;
        }
    }
}