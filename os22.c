#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int volatile done = 0;
void handler(int sig, siginfo_t *siginfo, void *context)
{
	printf("Signal %d was caught\n", sig);
	printf("your UID is %d\n", siginfo->si_uid);
	printf("your PID is %d\n", siginfo->si_pid);
	done = 1;
}

int main()
{
	printf("Lebedev 37 \n");

	int pid = getpid();
	printf("Ok, let's go - kill me (%d) and I'll tell you who you are.\n", pid);
	struct sigaction sa;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	if (sigaction(SIGINT, &sa, NULL) != 0)
	{
		return(1);
	}
	while(!done)
	{
	}
	printf("Told you so!\n");
	return 0;
}




//Example 1
// void sighandler(int signum)
// {
// 	printf("Caught signal %d, coming out...\n", signum);
// 	exit(1);
// }
	// signal(SIGINT, sighandler);
	// while(1);


//Example 2
// int count = 0;
// void SigHndlr (int s)
// {
// 	printf("\n I got SIGINT %d time(s) \n", ++count);
// 	if (count == 5) signal(SIGINT, SIG_DFL);
// 	else signal (SIGINT, SigHndlr);
// }

	//	signal (SIGINT, SigHndlr);
	//	while(1);

//Example 3
// int volatile count;

// void handler(int sig)
// {
// 	printf("signal %d ouch that hurt\n", sig);
// 	count++;
// }

	// int pid = getpid();
	// printf("ok, let's go, kill me (%d) if you can! \n", pid);
	// struct sigaction sa;
	// sa.sa_handler = handler;
	// sigemptyset(&sa.sa_mask);
	// sigaction(SIGINT, &sa, NULL);
	// while (count != 4)
	// {
	// 	kill (pid, SIGINT);
	// }
	// printf("I've had enough!\n");

//Example 4
// int volatile count;

// void handler(int sig)
// {
// 	printf("signal %d ouch that hurt\n", sig);
// 	count++;
// }

	// struct sigaction sa;
	// int pid = getpid();
	// printf("ok, let's go, kill me (%d) if you can! \n", pid);
	// sa.sa_handler = handler;
	// sigemptyset(&sa.sa_mask);
	// if (sigaction(SIGINT, &sa, NULL) != 0)
	// {
	// 	return(1);
	// }
	// while (count != 4)
	// {
	// }
	// printf("I've had enough!\n");


//Example 5
// const char *tempfile = "abc1";
// void sighandler(int signum)
// {
// 	printf("Caught signal %d...\n", signum);
// 	unlink(tempfile);
// 	exit(0);
// }

	// signal(SIGINT, sighandler);
	// creat(tempfile, 0666);
	// sleep(8);
	// unlink(tempfile);


//Example 6

// void sighandler(int sign)
// {
// 	printf("Caught signal %d: waiting... \n", sign);
// 	signal(SIGALRM, sighandler);
// }

	// char s[80];
	// int pid;
	// signal(SIGALRM, sighandler);
	// if (pid=fork()) //parent
	// {
	// 	for(;;)
	// 	{
	// 		sleep(5);
	// 		kill(pid, SIGALRM); //to child
	// 	}
	// }
	// else
	// {
	// 	printf("Input a name ... \n");
	// 	for(;;)
	// 	{
	// 		printf("Name: ");
	// 		if (fgets(s, sizeof(s), stdin) != NULL) break;
	// 	}
	// 	printf("OK! \n");
	// 	kill(getppid(), SIGKILL); //to parent
	// }


//Example 7

// void handler (int sig)
// {
// 	printf ("signal %d was caught\n", sig);
// 	exit(1);
// 	return;
// }

// int not_so_good()
// {
// 	int x = 0;
// 	return 1 % x;
// }

	// struct sigaction sa;
	// printf("Ok, let's go - I'll catch my own error.\n");
	// sa.sa_handler = handler;
	// sigemptyset(&sa.sa_mask);
	// //and now we catch ,,, FPE signals
	// sigaction(SIGFPE, &sa, NULL);
	// not_so_good();
	// printf("Will probably not write this.\n");
	// 