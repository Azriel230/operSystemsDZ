#include <iostream>
#include <thread>
#include <Windows.h>
#include <fstream>
#include <string>

int user = 0;
HANDLE sem1 = CreateSemaphore(NULL, 0, 1, L"sem1");
HANDLE sem2 = CreateSemaphore(NULL, 0, 1, L"sem2");


void reader() 
{
	std::ifstream file_in;
	while (true)
	{
		file_in.open("chat.txt");
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
		std::string text;
		if (!file_in.is_open())
		{
			std::cout << "File is not opened!";
			exit(0);
		}
		file_in >> text;
		std::cout << "User " << ((user + 1) % 2) << ": " << text << std::endl;
		file_in.close();
	}
}

void writer()
{
	while (true) {

		std::ofstream file_out;
		file_out.open("chat.txt");
		if (!file_out.is_open())
		{
			std::cout << "Error! Chat file isn't opened!";
			exit(EXIT_FAILURE);
		}
		char text[1024];
		//std::cout << "User " << user << ": ";
		std::cin.getline(text, 1024);
		//std::cout << std::endl;
		file_out << text << "\n";
		file_out.close();
		if (user == 1)
			ReleaseSemaphore(sem2, 1, NULL);
		else
			ReleaseSemaphore(sem1, 1, NULL);
	}
}

void createFile()
{
	std::ofstream createConfig;
	createConfig.open("config.txt", std::ios::out);
	createConfig << user;
	createConfig.close();

	std::ofstream createChat;
	createChat.open("chat.txt", std::ios::out);
	createChat.close();
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
	std::thread writeThread(writer);
	std::thread readThread(reader);

	writeThread.join();
	readThread.join();

	return 0;
}