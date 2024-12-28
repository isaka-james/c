int main(void){
	char message[] = "Hello There!$";
	asm(
			"mov ah, 0x09\n"
			"lea dx, message\n"
			"int 0x21\n"
	   );
	return 0;
}
