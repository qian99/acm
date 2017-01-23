在[1,r)范围内查找值v，返回下标
假设a数组已经按从小到大排序
失败返回-1

int bs(int a[],int l,int h,int v)
{
	int m;
	while(l<h)
	{
		m=(l+h)>>1;
		if(a[m]==v)
		{
			return m;
		}
		if(a[m]<v)
		{
			l=m+1;
		}
		else
		{
			h=m;
		}
	}
	return -1;
}




大于等于v的第一个值
传入参数必须l<=h
返回值l总是合理的

int bs(int a[],int l,int h,int v)
{
	int m;
	while(l<h)
	{
		m=(l+h)>>1;
		if(a[m]<v)
		{
			l=m+1;
		}
		else
		{
			h=m;
		}
	}
	return l;
}