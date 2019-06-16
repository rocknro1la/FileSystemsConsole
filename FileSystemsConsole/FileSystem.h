#pragma once
#include "windows.h"
#include <iostream>
#include <string>

typedef struct
{
	BYTE Padding1[3];
	BYTE OEMName[8];
} OEM;

class FileSystem
{
protected:
	HANDLE FileHandle;
	DWORD TotalClusters;
	BYTE ClusterFactor;
	DWORD BytesPerCluster;
	BYTE OEMName[8];
public:
	FileSystem();
	~FileSystem();
	virtual bool ReadClusters(ULONGLONG startCluster, DWORD numberOfClusters, BYTE *outBuffer) = 0;
	virtual void Print() = 0;
	DWORD GetTotalClusters() const;
	DWORD GetBytesPerCluster() const;
	BYTE* GetOem();
	void Close();
};

