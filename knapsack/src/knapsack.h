
typedef struct
{
	int* w;//wΪ����[����]
	int* v;//vΪ��ֵ[����]
	int* b;//b��ʾ�Ƿ�ѡ��[���]
	int* buf;//������õĻ��壬������w,v,b��ͬ
	int len;//lenΪ���ݳ���
	int maxw;//������������

}KNAPSACK_PROBLEM;

//�ɹ������ܵ�װ����ֵ��ʧ�ܷ��ظ�ֵ
typedef int (*knapsack_solv_func)(KNAPSACK_PROBLEM* problem);

int knapsack_solv(knapsack_solv_func func);