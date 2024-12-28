#include<unistd.h>

int main(void){
	const char *message = "Hello There!\n";
	write(1,message,13);
	return 0;
}
