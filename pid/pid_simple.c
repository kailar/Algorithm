#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void pid_simple()
{
	int i;
	float input[100];
	float output[100];


	float K=0.4;
	float I=0.5;
	float P=0.05;

	float err=0,intErr=0,lastErr=0;

	for(i=0;i<5;i++) input[i]=1.0;
	for(i=5;i<30;i++) input[i]=i*0.5;//+(rand()%100)/1000.f;
	for(i=30;i<50;i++) input[i]=i*0.2;//+(rand()%100)/1000.f;
	for(i=50;i<100;i++) input[i]=50*0.2;//+(rand()%100)/1000.f;
	output[0]=1.0;
	for(i=1;i<100;i++)
	{
		float delta;
		lastErr=err;
		err=input[i]-output[i-1];
		intErr+=err;
		delta=K*err+I*intErr;//+P*(err-lastErr);
		output[i]=output[i-1]+delta;
	}
	

	for(i=0;i<100;i++)
	{
		printf("i=%3d i[%0.7f] o[%0.7f] d[%+e]\r\n",i,input[i],output[i],input[i]-output[i]);
	}
}