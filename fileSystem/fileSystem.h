#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
//#include <windows.h>
#include <mutex>

struct File
{
	std::string name;
	std::string data;
	int size;
};

class FileSystem
{
	std::vector<File*> m_files;
	int m_countFiles{ 0 };
	std::mutex m_mutex;
public:
	FileSystem();
	FileSystem(int countFiles);
	~FileSystem();

	File* searchFile(std::string name);
	void createFile(std::string name);
	void deleteFile(std::string name);
	void readFile(std::string name);
	void writeFile(std::string name, std::string text);
	void fileSystemInfo();
};