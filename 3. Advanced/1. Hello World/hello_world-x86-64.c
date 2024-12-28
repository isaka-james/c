int main(void){
	const char *message = "Hello There!\n";
	asm(
			"mov $1, %%rax\n"
			"mov $1, %%rdi\n"
			"mov %0, %%rsi\n"
			"mov $13, %%rdx\n"
			"syscall\n"
			:
			: "r"(message)
			: "%rax", "%rdi", "%rsi", "%rdx"
	   );
	return 0;
}
