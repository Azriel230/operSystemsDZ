#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define IO_TIME 30
int io_op(float ratio, int exect)
{
	int io = ((float)rand())/RAND_MAX < ratio;
	if (io)
	{
		io = (int)trunc(((float)rand())/RAND_MAX * (exect - 1)) + 1;
	}
	return io;
}

//Структура задания
typedef struct job
{
	int id;
	int arrival;
	int unblock;
	int exectime;
	int response;
	int turnaround;
	int waitingtime;
	float ioratio;
	struct job *next;
} job;

//Структура, описывающая различные задания
typedef struct spec
{
	int arrival;
	int exectime;
	float ioratio;
} spec;


// spec specs [ ] = {
// 	{ 0, 10, 0.0 },
// 	{ 0, 30, 0.7 },
// 	{ 0, 20, 0.0 },
// 	{ 40, 80, 0.4 },
// 	{ 60, 30, 0.3 },
// 	{120, 90, 0.3 },
// 	{120, 40, 0.5 },
// 	{140, 20, 0.2 },
// 	{160, 10, 0.3 },
// 	{180, 20, 0.3 },
// 	{0 , 0 , 0} // dummy job
// };

// spec specs [ ] = {
// 	{ 0, 13, 0.0 },
// 	{ 0, 4, 0.0 },
// 	{ 0, 1, 0.0 },
// };

// spec specs [ ] = {
// 	{ 0, 5, 0.0 },
// 	{ 0, 3, 0.0 },
// 	{ 0, 7, 0.0 },
// 	{ 0, 1, 0.0 },
// };

spec specs [ ] = {
	{ 0, 10, 0.0 },
	{ 0, 30, 0.7 },
	{ 0, 20, 0.0 },
	{ 0, 80, 0.4 },
	{ 0, 30, 0.3 },
	{0 , 0 , 0} // dummy job
};

job *readyq = NULL;
job *blockedq = NULL;
job *doneq = NULL;

//Блокирует задания и упорядочивает их по времени разблокировки
void block(job *this)
{
	job *nxt = blockedq;
	job *prev = NULL;
	while(nxt != NULL)
	{
		if (this->unblock < nxt->unblock)
		{
			break;
		}
		prev = nxt;
		nxt = nxt->next;
	}
	this->next = nxt;
	if (prev != NULL)
	{
		prev->next = this;
	}
	else
	{
		blockedq = this;
	}
	return;

}

void ready(job *this)
{
	job *nxt = readyq;
	job *prev = NULL;
	while (nxt != NULL /*&& this->exectime > nxt->exectime*/) 
	{
		prev = nxt;
		nxt = nxt->next;
	}
	this->next = nxt;
	if (prev == NULL)
	{
		readyq = this;
	}
	else
	{
		prev->next = this;
	}
	return;
}

void done (job *this)
{
	this->next = doneq;
	doneq = this;
	return;
}

void unblock(int time)
{
	while (blockedq != NULL && blockedq->unblock <= time)
	{
		job *nxt = blockedq;
		blockedq = nxt->next;
		printf("(%4d) unblock job %2d\n", time, nxt->id);
		ready(nxt);
	}
}

void waiting_time(int time)
{
	job *waiting = readyq;
	while (waiting != NULL)
	{
		waiting->waitingtime += time;
		waiting = waiting->next;
	}
}

int schedule(int time, int slot) 
{
	if (readyq != NULL)
	{
		job *nxt = readyq;
		readyq = readyq->next;
		if (nxt->response == 0)
		{
			nxt->response = time - nxt->arrival;
		}
		int left = nxt->exectime;
		int exect = (left < slot) ? left : slot;
		int io = 0;
		if (exect > 1)
		{
			io = io_op(nxt->ioratio, exect);
			if (io)
				exect = io;
		}
		nxt->exectime -= exect;
		printf("(%4d) run job %2d for %3d ms", time, nxt->id, exect);
		waiting_time(exect);
		if(nxt->exectime == 0)
		{
			nxt->turnaround = time + exect - nxt->arrival;
			printf(" = done\n");
			done(nxt);
		}
		else
		{
			if (io)
			{
				nxt->unblock = time + exect + IO_TIME;
				block(nxt);
				printf(" = %3d left - Blocked \n", nxt->exectime);
			}
			else
			{
				ready(nxt);
				printf(" = %3d left\n", nxt->exectime);
			}
	
		}
		return exect;
	}
	else
	{
		return 1;
	}
}

//Создает задания по массиву спецификаций и блокирует их.
void init() 
{
	int i = 0;
	while (specs[i].exectime != 0)
	{
		job *new = (job*) malloc(sizeof(job));
		new->id = i+1;
		new->arrival = specs[i].arrival;
		new->unblock = specs[i].arrival;
		new->exectime = specs[i].exectime;
		new->response = 0; 
		new->turnaround = 0;
		new->waitingtime = 0;
		new->ioratio = specs[i].ioratio;
		block(new);
		i++;
	}
}




int main(int argc, char* argv[])
{
	printf("Lebedev 37\n");

	int slot = 10; // квант времени
	if (argc == 2)
		slot = atoi(argv[1]);

	init();
	int time = 0;
	float tt = 0;
	float wt = 0;
	float rt = 0;
	int countOfJobs = 0;

	while(blockedq != NULL || readyq != NULL)
	{
		unblock(time);
		int tick = schedule(time, slot);
		time += tick;
	}

	job *jobsDone = doneq;
	while (jobsDone != NULL)
	{
		tt += jobsDone->turnaround;
		wt += jobsDone->waitingtime;
		rt += jobsDone->response;
		countOfJobs++;
		jobsDone = jobsDone->next;
	}

	tt = tt / countOfJobs;
	wt = wt / countOfJobs;
	rt = rt / countOfJobs;
	printf("\nTotal execution time is %d \n", time);
	printf("tt = %.3f, wt = %.3f, rt = %3f\n", tt, wt, rt);

	return 0;
}