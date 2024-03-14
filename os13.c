#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>


int main()
{
	printf("Lebedev 37\n");

	int pid = fork();
	if (pid == 0)
	{
		int fd = open("f1.txt", O_RDWR | O_CREAT);
		dup2(fd, 1);
		close(fd);
		execl("myprint", "myprint", NULL);
		printf("this will only happen if exec fails\n");
	}
	else
	{
		wait(NULL);
		printf("we're done\n");
	}
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

	//Example 4		int pid = fork();
	// if (pid == 0)
	// {
	// 	printf("I am a child %d\n", getpid());
	// 	sleep(10);
	// 	printf("end sleep %d\n", getpid());
	// 	return(42);
	// }
	// else
	// {
	// 	sleep(20);
	// 	printf("I am %d. My child is called %d\n", getpid(), pid);
	// 	int res;
	// 	wait(&res);
	// 	if (WIFEXITED(res))
	// 		printf("My child has trrminated %d\n", WEXITSTATUS(res));
	// 	printf("and again %d sleep \n", getpid());
	// 	sleep(10);
	// }
	// printf("Finish %d\n", getpid());

	//Example 5
	// int pid;
	// int x = 123;
	// pid = fork();
	// if (pid == 0)
	// {
	// 	printf("child: x is %d\n", x);
	// 	x = 42;
	// 	sleep(1);
	// 	printf("child: x is %d\n", x);
	// }
	// else
	// {
	// 	printf("parent: x is %d\n", x);
	// 	x = 13;
	// 	sleep(1);
	// 	printf("parent: x is %d\n", x);
	// 	wait(NULL);
	// }

	//Example 6
	//	int pid;
	// int x = 123;
	// pid = fork();
	// if (pid == 0)
	// {
	// 	printf("child: x is %d and address is 0x%p\n", x, &x);
	// 	x = 42;
	// 	sleep(1);
	// 	printf("child: x is %d and address is 0x%p\n", x, &x);
	// }
	// else
	// {
	// 	printf("parent: x is %d and address is 0x%p\n", x, &x);
	// 	x = 13;
	// 	sleep(1);
	// 	printf("parent: x is %d and address is 0x%p\n", x, &x);
	// 	wait(NULL);
	// }

	//Example 7
	// int pid;
	// int x = 123;
	// pid = fork();
	// if (pid == 0)
	// {
	// 	printf("I'm a child %d with parent %d\n", getpid(), getppid());
	// }
	// else
	// {
	// 	printf("I'm a parent %d with parent %d\n", getpid(), getppid());
	// 	wait(NULL);
	// }

	//Example 8
	// int pid = fork();
	// if (pid == 0)
	// {
	// 	int child = getpid();
	// 	printf("I'm a child %d in group %d\n", child, getpgid(child));
	// }
	// else
	// {
	// 	int parent = getpid();
	// 	printf("I'm a parent %d in group %d\n", parent, getpgid(parent));
	// 	wait(NULL);
	// }

	//Example 9
	// int pid = fork();
	// if (pid == 0)
	// {
	// 	int child = getpid();
	// 	printf("Child (%d): parent %d, group %d\n", getpid(), getppid(), getpgid(child));
	// 	sleep(8);
	// 	printf("Child (%d): parent %d, group %d\n", getpid(), getppid(), getpgid(child));
	// 	sleep(4);
	// }
	// else
	// {
	// 	int parent = getpid();
	// 	printf("Parent (%d): parent %d, group %d\n", getpid(), getppid(), getpgid(parent));
	// 	sleep(4);
	// 	int zero = 0;
	// 	int u = 5 / zero;
	// }

	// Example 10
	// pid_t pid, ppid;
	// int a = 0;
	// (void)fork();
	// a = a+1;
	// pid = getpid();
	// ppid = getppid();
	// printf("My pid = %d, my ppid = %d, result = %d\n", (int)pid, (int)ppid, a);

	//Example 11
	// int pid = fork();
	// if (pid == 0)
	// {
	// 	int child = getpid();
	// 	printf("Child (%d): session %d\n", getpid(), getsid(child));
	// }
	// else
	// {
	// 	int parent = getpid();
	// 	printf("Parent (%d): session %d\n", getpid(), getsid(parent));
	// }