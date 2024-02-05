#include <stdio.h>
#include "main.h"
#include<pthread.h>
#include"DATA_Thread.h"
#include"CTRL_Thread.h"

int main(){

	int net = 0;
	pthread_t DATA_Task;
	pthread_t CTRL_Task;

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

	pthread_join(DATA_Task,NULL);
	pthread_join(CTRL_Task,NULL);



	//project1();
	//project2();
	//project3();
	//project4();
	//project5();

	return 0;
}
