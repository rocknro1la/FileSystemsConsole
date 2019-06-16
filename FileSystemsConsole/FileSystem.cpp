#include "pch.h"
#include "FileSystem.h"


FileSystem::FileSystem()
{
}


FileSystem::~FileSystem()
{
}

void FileSystem::Print()
{
}

DWORD FileSystem::GetTotalClusters() const
{
	return TotalClusters;
}

DWORD FileSystem::GetBytesPerCluster() const
{
	return BytesPerCluster;
}

BYTE * FileSystem::GetOem()
{
	return OEMName;
}

void FileSystem::Close()
{
	CloseHandle(FileHandle);
}
