#include <stdio.h>
#include "main.h"
#include<pthread.h>
#include"DATA_Thread.h"
#include"CTRL_Thread.h"

volatile int testA = 1;

int main(){

	if (testA == 1) {
		return 0;
	}

	printf("%d",TestData);

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


#if 2
	printf("mmmmmmmmm");
#endif


	//project1();
	//project2();
	//project3();
	//project4();
	//project5();

	return 0;
}

void* TEST_Thread(void* arg) {
	testA = 10;
	return NULL;
}