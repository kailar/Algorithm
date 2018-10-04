#include <stdio.h>
#include <math.h>

/*黑科技来自游戏雷神之锤3的源代码*/

float sqrt_dark(float x) 
{ 
    float result = x; 
    float xhalf = 0.5f*result; 
    int i = *(int*)&result; 
	if(x == 0) return 0; 
    i = 0x5f375a86- (i>>1); // what the fuck? 
    result = *(float*)&i; 
    result = result*(1.5f-xhalf*result*result); // Newton step, repeating increases accuracy 
    result = result*(1.5f-xhalf*result*result); 
    return 1.0f/result; 
}
