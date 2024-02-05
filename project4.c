#include<stdio.h>
#include"lib.h"

void project4(void) {
	Message gMessage = { 0x12,0x222 };
	if (gMessage.A == 0x12) {
		printf("yes");
	}
	else {
		printf("no");
	}
}