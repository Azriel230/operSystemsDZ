#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	printf("Lebedev 37\n");

	int pid = fork();
	if (pid == 0)
	{
		printf("I am a child %d\n", getpid());
		sleep(10);
		printf("end sleep %d\n", getpid());
		return(42);
	}
	else
	{
		sleep(20);
		printf("I am %d. My child is called %d\n", getpid(), pid);
		int res;
		wait(&res);
		if (WIFEXITED(res))
			printf("My child has trrminated %d\n", WEXITSTATUS(res));
		printf("and again %d sleep \n", getpid());
		sleep(10);
	}
	printf("Finish %d\n", getpid());
	return 0;
}



	//PRESENTATION A

	//Example 1
	// foo :
	// printf("the code: %p\n", &&foo);
	// fgetc(stdin);


	//char global[] = "This is a global string"; Example2 - глобальная переменная

	//Example 2
	// int pid = getpid();
	// foo:
	// printf("process id: %d\n", pid);
	// printf("global string: %p\n", &global);
	// printf("the code: %p\n", &&foo);
	// printf("\n\n /proc/%d/maps \n\n", pid);
	// char command [50];
	// sprintf(command, "cat /proc/%d/maps", pid);
	// system(command);

	//Example 3
	// int pid = getpid();
	// unsigned long p = 0x1;
	// printf("p (0x%1x): %p \n", p, &p);
	// printf("process id: %d\n", pid);
	// printf("\n\n /proc/%d/maps \n\n", pid);
	// char command [50];
	// sprintf(command, "cat /proc/%d/maps", pid);
	// system(command);

	//Example 4
	// 	void zot(unsigned long* stop)
	// {
	// 	unsigned long r = 0x3;
	// 	unsigned long* i;
	// 	for (i = &r; i <= stop; i++)
	// 	{
	// 		printf("%p 0x%1x \n", i, *i);
	// 	}	
	// }

	// void foo(unsigned long* stop)
	// {
	// 	unsigned long q = 0x2;
	// 	zot(stop);
	// }

	// int main()
	// {
	// 	printf("Lebedev 37\n");

	// 	int pid = getpid();
	// 	unsigned long p = 0x1;
	// 	foo(&p);
	// 	back:
	// 	printf("	p: %p\n", &p);
	// 	printf("	back: %p\n", &&back);

	// 	printf("process id: %d\n", pid);
	// 	printf("\n\n /proc/%d/maps \n\n", pid);
	// 	char command [50];
	// 	sprintf(command, "cat /proc/%d/maps", pid);
	// 	system(command);
	// 	return 0;
	// }


	//Example 5
	// int pid = getpid();
	// char* heap = malloc(20);
	// printf("the heap valriable at: %p\n", &heap);
	// printf("pointing to: %p\n", heap);

	// printf("process id: %d\n", pid);
	// printf("\n\n /proc/%d/maps \n\n", pid);
	// char command [50];
	// sprintf(command, "cat /proc/%d/maps", pid);
	// system(command);

	//Example 6
	// int pid = getpid();
	// long *heap = (unsigned long*)calloc(40, sizeof(unsigned long));
	// printf("heap[2]: 0x%1x \n", heap[2]);
	// printf("heap[1]: 0x%1x \n", heap[1]);
	// printf("heap[0]: 0x%1x \n", heap[0]);
	// printf("heap[-1]: 0x%1x \n", heap[-1]);
	// printf("heap[-2]: 0x%1x \n", heap[-2]);
	// free(heap);
	// printf("heap[2]: 0x%1x \n", heap[2]);
	// printf("heap[1]: 0x%1x \n", heap[1]);
	// printf("heap[0]: 0x%1x \n", heap[0]);
	// printf("heap[-1]: 0x%1x \n", heap[-1]);
	// printf("heap[-2]: 0x%1x \n", heap[-2]);

	// printf("process id: %d\n", pid);
	// printf("\n\n /proc/%d/maps \n\n", pid);
	// char command [50];
	// sprintf(command, "cat /proc/%d/maps", pid);
	// system(command);




	//PRESENTATION B
	
	//Example 1
	// int pid = fork();
	// if (pid == 0)
	// {
	// 	printf("I am a child %d\n", getpid());
	// }
	// else
	// {
	// 	printf("I am %d. My child is called %d\n", getpid(), pid);
	// }
	// printf("Finish %d\n", getpid());

	//Example 2
	// int pid = fork();
	// if (pid == 0)
	// {
	// 	printf("I am a child %d\n", getpid());
	// }
	// else
	// {
	// 	printf("I am %d. My child is called %d\n", getpid(), pid);
	// 	wait(NULL);
	// 	printf("My child has trrminated\n");
	// }
	// printf("Finish %d\n", getpid());

	//Example 3
	// int pid = fork();
	// if (pid == 0)
	// {
	// 	printf("I am a child %d\n", getpid());
	// 	return(42);
	// }
	// else
	// {
	// 	printf("I am %d. My child is called %d\n", getpid(), pid);
	// 	int res;
	// 	wait(&res);
	// 	if (WIFEXITED(res))
	// 		printf("My child has trrminated %d\n", WEXITSTATUS(res));
	// }
	// printf("Finish %d\n", getpid());