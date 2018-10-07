
typedef struct
{
	int* w;//w为重量[输入]
	int* v;//v为价值[输入]
	int* b;//b表示是否选中[输出]
	int* buf;//计算可用的缓冲，长度与w,v,b相同
	int len;//len为数据长度
	int maxw;//容许的最大重量

}KNAPSACK_PROBLEM;

//成功返回总的装包价值，失败返回负值
typedef int (*knapsack_solv_func)(KNAPSACK_PROBLEM* problem);

int knapsack_solv(knapsack_solv_func func);