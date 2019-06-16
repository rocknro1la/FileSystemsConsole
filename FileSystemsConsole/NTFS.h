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
} NTFS_BootRecord;

class NTFS :	
	public FileSystem
{
public:
	NTFS(BYTE* BootRecord, HANDLE FileHandle);
	~NTFS();
	virtual bool ReadClusters(ULONGLONG startCluster, DWORD numberOfClusters, BYTE *outBuffer);
	std::vector<DWORD> Buffer;
	void Print();
};

