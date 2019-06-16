#include "pch.h"
#include "exFAT.h"

exFAT::exFAT(BYTE * BootRecord, HANDLE FileHandle)
{
	exFAT_BootRecord* bootRecord = (exFAT_BootRecord*)BootRecord;
	memcpy(OEMName, bootRecord->OEMName, sizeof(OEMName));
	DWORD BytesPerSector = (DWORD)pow(2, (long)bootRecord->BytesPerSector);
	DWORD SectorsPerCluster = (DWORD)pow(2, (long)bootRecord->SectorsPerCluster);
	BytesPerCluster = SectorsPerCluster * BytesPerSector;
	TotalClusters = bootRecord->NumberOfClusters;
	exFAT::FileHandle = FileHandle;
}

exFAT::~exFAT()
{
}

bool exFAT::ReadClusters(ULONGLONG startCluster, DWORD numberOfClusters, BYTE * outBuffer)
{
	ULONGLONG startOffset = startCluster * BytesPerCluster;
	DWORD bytesToRead = numberOfClusters * BytesPerCluster;
	DWORD bytesRead;
	LARGE_INTEGER sectorOffset;
	sectorOffset.QuadPart = startOffset;

	unsigned long currentPosition = SetFilePointer(
		FileHandle,
		sectorOffset.LowPart,
		&sectorOffset.HighPart,
		FILE_BEGIN
	);

	if (currentPosition != sectorOffset.LowPart)
	{
		std::cout << "currentPosition != sectorOffset.LowPart" << std::endl;
		exit(GetLastError());
	}

	bool readResult = ReadFile(
		FileHandle,
		outBuffer,
		bytesToRead,
		&bytesRead,
		NULL
	);

	if (!readResult || bytesRead != bytesToRead)
	{
		std::cout << "Can not show filesystem" << std::endl;
		exit(GetLastError());
	}
	else
	{
		Buffer.clear();
		int i = 0;
		while (i != bytesToRead) {
			Buffer.push_back(int(*outBuffer));
			outBuffer++;
			i++;
		}
	}
	return true;
}

void exFAT::Print()
{
	int i = 0;
	while (i != Buffer.size()) {
		std::cout << std::hex << DWORD(Buffer[i]) << " ";
		i++;
		if (i % 16 == 0) std::cout << std::endl;
	}
	Buffer.clear();
}
