#pragma once
#include "FileSystem.h"
#include <vector>

typedef struct
{
	BYTE Padding1[3];
	BYTE OEMName[8];
	BYTE BytesPerSector[2];
	BYTE SectorsPerCluster;
	BYTE Padding2[23];
	ULONGLONG NumberOfClusters;
} FAT32_BootRecord;

class FAT32 :
	public FileSystem
{
public:
	FAT32(BYTE* BootRecord, HANDLE FileHandle);
	~FAT32();
	virtual bool ReadClusters(ULONGLONG startCluster, DWORD numberOfClusters, BYTE *outBuffer);
	std::vector<DWORD> Buffer;
	void Print();
};
