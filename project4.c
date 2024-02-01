#include<stdio.h>
#include"lib.h"

void project4(void) {
	Message gMessage = { 0x123,0x222 };
	if (gMessage.A == 273) {
		printf("yes");
	}
	else {
		printf("no");
		printf("%p\n",gMessage.A);
	}
}