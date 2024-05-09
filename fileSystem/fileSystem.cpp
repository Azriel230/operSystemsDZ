#include "fileSystem.h"

FileSystem::FileSystem()
{
}

FileSystem::FileSystem(int countFiles)
{
	m_countFiles = countFiles;
}

FileSystem::~FileSystem()
{
	for (auto& it : m_files)
		delete it;
	m_files.clear();
}

File* FileSystem::searchFile(std::string name)
{
	for (auto& it : m_files)
	{
		if (it->name == name)
			return it;
	}
	return nullptr;
}

void FileSystem::createFile(std::string name)
{
	m_mutex.lock();

	if (m_files.size() == m_countFiles)
	{
		std::cout << "Error! File System's memory is full! Can't create a new file!\n";
		m_mutex.unlock();
		return;
	}

	if (searchFile(name) != nullptr)
	{
		std::cout << "file " << name << " is already exist\n";
		m_mutex.unlock();
		return;
	}

	File* file = new File;
	file->name = name;
	file->data = "";
	file->size = 0;

	m_files.push_back(file);

	m_mutex.unlock();
}

void FileSystem::deleteFile(std::string name)
{
	m_mutex.lock();

	if (searchFile(name) == nullptr)
	{
		std::cout << "file " << name << " is not exist\n";
		m_mutex.unlock();
		return;
	}

	for (auto it = m_files.begin(); it != m_files.end(); ++it)
	{
		if ((*it)->name == name)
		{
			delete (*it);
			m_files.erase(it);
			m_mutex.unlock();
			return;
		}
	}

	m_mutex.unlock();
}

void FileSystem::readFile(std::string name)
{
	m_mutex.lock();

	if (searchFile(name) == nullptr)
	{
		std::cout << "You can't read file " << name << ", it isn't exist\n";
		m_mutex.unlock();
		return;
	}

	File* file = searchFile(name);

	std::cout << "Read file " << file->name << ": " << file->data << std::endl;

	m_mutex.unlock();
}

void FileSystem::writeFile(std::string name, std::string text)
{
	m_mutex.lock();

	if (searchFile(name) == nullptr)
	{
		std::cout << "You can't write in file " << name << ", it isn't exist\n";
		m_mutex.unlock();
		return;
	}

	File* file = searchFile(name);
	file->data = text;
	file->size = text.size();
	std::cout << "Write in file " << file->name << ": " << file->data << " | size = " << file->size << std::endl;

	m_mutex.unlock();
}

void FileSystem::fileSystemInfo()
{
	m_mutex.lock();
	
	std::cout << std::endl << "FILE_SYSTEM_INFO:\n";
	std::cout << "Amount of files = " << m_files.size() << std::endl;
	std::cout << "Amount of max files = " << m_countFiles << std::endl;
	for (const auto& it : m_files)
	{
		std::cout << "file <" << it->name << ">: size = " << it->size << std::endl;
	}
	std::cout << "File System's memory is " << (m_files.size() * 100 / m_countFiles) << "% full (" << m_files.size() << " out of " << m_countFiles << ")" << std::endl << std::endl;

	m_mutex.unlock();
}