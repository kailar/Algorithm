#include "bench.h"
#include "knapsack.h"

static int maxv(int a,int b)
{
	return a>b?a:b;
}
static int _knapsack_solv_recursive_bestv=0;
static void _knapsack_solv_recursive(KNAPSACK_PROBLEM *p,int i,int sumw,int sumv)
{
	if(i==p->len)
	{
		if(sumv>_knapsack_solv_recursive_bestv)
		{
			_knapsack_solv_recursive_bestv=sumv;
			memcpy(p->buf,p->b,p->len*sizeof(int));
		}
	}
	else
	{
		p->b[i]=0;
		_knapsack_solv_recursive(p,i+1,sumw,sumv);
		if(sumw>=p->w[i])
		{
			p->b[i]=1;
			_knapsack_solv_recursive(p,i+1,sumw-p->w[i],sumv+p->v[i]);
		}
	}
}

int knapsack_solv_recursive(KNAPSACK_PROBLEM *p)
{
	_knapsack_solv_recursive(p,0,p->maxw,0);
	memcpy(p->b,p->buf,p->len*sizeof(int));
	return _knapsack_solv_recursive_bestv;
}

int knapsack_solv_dynamic(KNAPSACK_PROBLEM *p)
{
	int*  buf=(int*)malloc(p->len*(p->maxw+1)*sizeof(int));
	int** a=(int**)malloc(p->len*sizeof(int*));/*a[i][j]:第0-i件物品在包剩余重量为j时的最高价值*/
	int i,j,w;
	for(i=0;i<p->len;i++)    a[i]=buf+i*(p->maxw+1);
	for(j=0;j<p->maxw+1;j++) a[0][j]=(j>=p->w[0])?p->v[0]:0;
	for(i=1;i<p->len;i++)
		for(j=0;j<p->maxw+1;j++)
	{
		if(j<p->w[i]) a[i][j]=a[i-1][j];/*当前物件超重:使用前一件物品重量为j的价值*/
		else a[i][j]=maxv(a[i-1][j-p->w[i]]+p->v[i],a[i-1][j]);
	}
	w=p->maxw;
	for(i=p->len-1;i>0;i--)
	{
		p->b[i]=a[i][w]!=a[i-1][w];
		w-=p->b[i]*p->w[i];
	}
	p->b[0]=a[0][w]>0;
	w=a[p->len-1][p->maxw];
	free(a);free(buf);
	return w;
}


int knapsack_test()
{
	//return knapsack_solv(knapsack_solv_recursive);
	return knapsack_solv(knapsack_solv_dynamic);

}