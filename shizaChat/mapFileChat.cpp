#include <iostream>
#include <fstream>
#include <thread>
#include <string>
#include <Windows.h>

constexpr auto MSIZE = 10000;
 
int user = 0;

HANDLE sem1 = CreateSemaphore(NULL, 0, 1, L"sem1");
HANDLE sem2 = CreateSemaphore(NULL, 0, 1, L"sem2");
HANDLE hFile = CreateFile(L"C:\\Users\\Azriel\\source\\repos\\shizaChat\\x64\\Debug\\chat.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
HANDLE hMapFile;
char* shared_memory;
char str[MSIZE];
int str_size;

void reader() {
	while (true) 
	{
		if (user == 1)
		{
			if (WaitForSingleObject(sem1, INFINITE) != WAIT_OBJECT_0)
				continue;
		}
		else
		{
			if (WaitForSingleObject(sem2, INFINITE) != WAIT_OBJECT_0)
				continue;
		}
		std::cout << "User " << ((user + 1) % 2) << ": " << shared_memory << std::endl;
	}
}

void writer() {

	while (true)
	{
		std::cin.getline(shared_memory, 1024);
		if (user == 1)
		{
			ReleaseSemaphore(sem2, 1, NULL);
		}
		else
		{
			ReleaseSemaphore(sem1, 1, NULL);
		}
	}
}

void createFile()
{
	std::ofstream createConfig;
	createConfig.open("config.txt", std::ios::out);
	createConfig << user;
	createConfig.close();
}

void getUserId()
{
	std::ifstream config;
	config.open("config.txt");
	if (!config.is_open())
	{
		createFile();
		config.open("config.txt");
	}
	config >> user;
	config.close();

	std::ofstream configOut;
	configOut.open("config.txt", std::ios::out);
	if (!configOut.is_open())
	{
		std::cout << "Error! Config file isn't opened!";
		exit(EXIT_FAILURE);
	}
	int newUser = (user + 1) % 2;
	configOut << std::to_string(newUser);
	configOut.close();
}

int main() 
{
	getUserId();

	if (OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, L"SharedMemory") == NULL) {
		hFile = CreateFile(L"text.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		hMapFile = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, MSIZE, L"SharedMemory");
	}
	else {
		hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, L"SharedMemory");
	}
	shared_memory = (char*)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);

	std::thread writeThread(writer);
	std::thread readThread(reader);

	writeThread.join();
	readThread.join();
}