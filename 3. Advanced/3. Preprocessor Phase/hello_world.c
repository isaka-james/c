#include<stdio.h>
#include "hello_world.h"

float hello_world(){
	return PI;
}

int main(void){
	float pi = hello_world();
	printf("Value of the PI: %f\n");
	return 0;
}

