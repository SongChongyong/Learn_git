# include <stdio.h>

int main()
{
	printf("%.3f\n", -0.0049);   //保留3位小数 
	printf("%.30f\n", -0.0049);  //保留3位小数 
	printf("%.3f\n", -0.00049);  // 保留3位小数
	printf("%f\n", 12.0/0.0);   //无穷大 
	printf("%f\n", -12.0/0.0);   //负无穷大 
	printf("%f\n", 0.0/0.0);   //nan无意义	  
} 
/*
-0.005
-0.004899999999999999800000000000
-0.000
1.#INF00
-1.#INF00
-1.#IND00
*/
