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
//使用二维数组可以求得最优解与最优序列
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

//使用一维数组只能求得最优解,不能得到最优序列,性能是knapsack_solv_dynamic的4倍左右
/*
态转移方程 c[i][j] = max{c[i-1][j], c[i-1][j-w[i]]+v[i]}
每一次c[i][j]改变的值只与c[i-1][x] {x:1...j}有关c[i-1][x]是前一次i循环保存下来的值，因此，可以将c缩减成一维数组
状态转移方程转换为 c[j] = max(c[j], c[j-w[i]]+v[i]);
*/
int knapsack_solv_dynamic_dim1(KNAPSACK_PROBLEM *p)
{
	int*  c=(int*)calloc(p->maxw+1,sizeof(int));//c[j]在i轮计算后表示在容重为j时装入前i个物品，所能获取的最做优值
	int i,j,w;
	for(i=0;i<p->len;i++)
		for(j=p->maxw;j>=p->w[i];j--)
	{
		/*
		a[j]计算时依赖a[j-p->w[i]]的值，a[j-p->w[i]]的值必须是i-1这轮循环的计算结果，否则无法完成递推
		如果j从0到p->maxw（正序），在取a[j-p->w[i]]的值时，它可能已经在本轮循环修改了，因为j-p->w[i]<j,循环时a[j-p->w[i]]会先修改
		所以，j在循环时要从p->maxw到0（倒序）
		*/
		 if(c[j]<=p->v[i]+c[j-p->w[i]])
		 {
			 c[j]=p->v[i]+c[j-p->w[i]];
		 }
	}
	w=c[p->maxw];
	free(c);
	return w;
}

int knapsack_test()
{
	//return knapsack_solv(knapsack_solv_recursive);
	//return knapsack_solv(knapsack_solv_dynamic);
	return knapsack_solv(knapsack_solv_dynamic_dim1);

}