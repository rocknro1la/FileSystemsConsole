#pragma once
#include "FileSystem.h"
#include "NTFS.h"
#include "exFAT.h"
#include "FAT32.h"
#include <iostream>
#include "Iterator.h"

class Factory
{
protected:
	Iterator *it;
public:
	DWORD NumberOfClusters;
	FileSystem * CreateFileSystem();
	void ShowFileSystem(FileSystem *fs);
	void ShowInfo(FileSystem *fs);
	void Close(FileSystem *fs);
	Iterator * GetIterator(FileSystem *fs);
	Factory();
	~Factory();
};

