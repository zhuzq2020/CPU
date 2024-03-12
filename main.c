#include <stdio.h>
#include "main.h"
#include<pthread.h>
#include"DATA_Thread.h"
#include"CTRL_Thread.h"
#include <math.h>
#include <dos.h>
#include <windows.h>

void* TEST_Thread(void* arg);

static int N_size_BWP = 1;

struct PUCCH_PUBLIC_RESOURCE_CONFIG
{
	int pucch_format;
	int first_symbol;
	int symbol_num;
	int prb_offset;
	int init_cs_index[4];
};


int main(){
	printf("%d", N_size_BWP);
	struct PUCCH_PUBLIC_RESOURCE_CONFIG pucch_public_resource_config[16] = {
		{0, 12, 2, 0,{0,3}} ,
		{0, 12, 2, 0,{0,4,8}},
		{0, 12, 2, 3,{0,4,8}},
		{1, 10, 3, 0,{0,6}},
		{1, 10, 3, 0,{0,3,6,9}},
		{1, 10, 3, 2,{0,3,6,9}},
		{1, 10, 1, 4,{0,3,6,9}},
		{1, 4, 1, 0,{0,6}},
		{1, 4, 2, 0,{0,3,6,9}},
		{1, 4, 2, 2,{0,3,6,9}},
		{1, 4, 3, 4,{0,3,6,9}},
		{1, 0, 3, 0,{0,6}},
		{1, 0, 1, 0,{0,3,6,9}},
		{1, 0, 2, 2,{0,3,6,9}},
		{1, 0, 3, 4,{0,3,6,9}},
		{1, 0, 0, N_size_BWP / 4,{0,3,6,9}}
	};

	//求次方
#if 0
	int a = 2;
	double b = 4;
	int result = pow(2, 4);
	//printf("% .2lf \n", result);//双精度浮点型数据，小数部分为两位
	printf("%d\n", result);
#endif

	int net = 0;
	pthread_t DATA_Task;
	pthread_t CTRL_Task;
	pthread_t TEST_Task;

	net = pthread_create(&DATA_Task, NULL, DATA_Thread, NULL);
	if (0 != net) {
		printf("create DATA_Task error");
		exit(-1);
	}

	net = pthread_create(&CTRL_Task, NULL, CTRL_Thread, NULL);
	if (0 != net) {
		printf("create CTRL_Task error");
		exit(-1);
	}

	net = pthread_create(&TEST_Task, NULL, TEST_Thread, NULL);
	if (0 != net) {
		printf("create CTRL_Task error");
		exit(-1);
	}

	//int n = 0;
	//while (testA != 10) {
	//	printf("%d", n++);
	//}

	pthread_join(DATA_Task,NULL);
	pthread_join(CTRL_Task,NULL);
	pthread_join(TEST_Task, NULL);


#if 0
	printf("mmmmmmmmm");
#endif


	//project1();
	project2();
	//project3();
	//project4();
	//project5();

	return 0;
}

void* TEST_Thread(void* arg) {

}

BOOL TestM(void) {
	printf("dafsdf");
	return TRUE;
}