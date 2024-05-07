#include <iostream>
#include <thread>
#include <time.h>
#include <functional>
#include <mutex>
#include <atomic>

/////////////////////////// ex 2: inc funct
unsigned int countBasic = 0;
unsigned int countMutex = 0;
std::mutex mutex;
std::atomic_uint countAtomic(0);
unsigned int num = 10000000;


void incrementBasic(unsigned int number)
{
	for (int i = 0; i < number; i++)
	{
		++countBasic;
	}
}

void incrementMutex(unsigned int number)
{
	for (int i = 0; i < number; i++)
	{
		mutex.lock();
		++countMutex;
		mutex.unlock();
	}
}

void incrementAtomic(unsigned int number)
{
	for (int i = 0; i < number; i++)
	{
		++countAtomic;
	}
}

void threadsIncBasic()
{
	std::thread thread1 = std::thread(incrementBasic, num);
	std::thread thread2 = std::thread(incrementBasic, num);

	thread1.join();
	thread2.join();

	std::cout << "CountBasic = " << countBasic << std::endl;
}

void threadsIncMutex()
{
	std::thread thread1 = std::thread(incrementMutex, num);
	std::thread thread2 = std::thread(incrementMutex, num);

	thread1.join();
	thread2.join();

	std::cout << "CountMutex = " << countMutex << std::endl;
}

void threadsIncAtomic()
{
	std::thread thread1 = std::thread(incrementAtomic, num);
	std::thread thread2 = std::thread(incrementAtomic, num);

	thread1.join();
	thread2.join();

	std::cout << "CountAtomic = " << countAtomic << std::endl;
}

int main()
{
	unsigned int timeStart = clock();
	threadsIncBasic();
	unsigned int timeEnd = clock();
	unsigned int timeTotal = timeEnd - timeStart;
	std::cout << "Running time the threadIncAtomic func is " << timeTotal << " ms." << std::endl;

	timeStart = clock();
	threadsIncMutex();
	timeEnd = clock();
	timeTotal = timeEnd - timeStart;
	std::cout << "Running time the threadIntMutex func is " << timeTotal << " ms." << std::endl;


	timeStart = clock();
	threadsIncAtomic();
	timeEnd = clock();
	timeTotal = timeEnd - timeStart;
	std::cout << "Running time the threadIntBasic func is " << timeTotal << " ms." << std::endl;

	return 0;
}