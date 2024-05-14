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
	std::mutex m_mutex;
};

class FileSystem
{
	std::vector<File*> m_files;
	int m_countFiles{ 0 };
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
