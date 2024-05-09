#include "fileSystem.h"

int main()
{
	FileSystem fs(10);
	fs.createFile("Aboba");
	fs.createFile("Bobr");
	fs.createFile("Dungeon");
	fs.fileSystemInfo();
	fs.writeFile("Aboba", "Imposter is sus");
	fs.writeFile("Bobr", "Bobre kurwa i kibitre kawaiii");
	fs.writeFile("Dungeon", "Hi, I'm Billy Herrington, stayn u today. I'm Dungeon Master!");
	fs.readFile("Bobr");
	fs.readFile("Aboba");
	fs.readFile("Dungeon");
	fs.fileSystemInfo();

	std::cout << "Error tests:" << std::endl;
	fs.createFile("Aboba");
	fs.readFile("MrBeast");
	fs.writeFile("BrBrBr", "123");
	fs.fileSystemInfo();
	fs.deleteFile("Bobr");
	fs.fileSystemInfo();
	fs.deleteFile("Aboba");
	fs.deleteFile("Dungeon");
	fs.fileSystemInfo();

	return 0;
}