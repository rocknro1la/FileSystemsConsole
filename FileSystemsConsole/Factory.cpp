#include "pch.h"
#include "Factory.h"


FileSystem * Factory::CreateFileSystem()
{
	HANDLE handle;
	BYTE StartBuffer[512];
	DWORD bytesRead;
	std::cout << "Enter disk letter: ";
	std::wstring DiskName;
	std::wcin >> DiskName;
	std::wstring fileName1 = L"\\\\.\\" + DiskName + L":";
	WCHAR * fileName = &fileName1[0];
	handle = CreateFileW(
		fileName,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (handle == INVALID_HANDLE_VALUE) {
		std::wcout << "Invalid handle value!";
		exit(GetLastError());
	}
	bool readResult = ReadFile(
		handle,
		StartBuffer,
		512,
		&bytesRead,
		NULL
	);
	if (!readResult) {
		std::cout << "Can not read" << std::endl;
		exit(GetLastError());
	}
	OEM* bootRecord = (OEM*)StartBuffer;
	std::string OEM((char *)bootRecord->OEMName, 8);
	FileSystem * fs;
	if (OEM == "NTFS    ") {
		return fs = new NTFS(StartBuffer, handle);
	}
	else if (OEM == "MSDOS5.0")
	{
		return fs = new FAT32(StartBuffer, handle);
	}
	else if (OEM == "EXFAT   ")
	{
		return fs = new exFAT(StartBuffer, handle);
	}	
}

void Factory::ShowFileSystem(FileSystem * fs)
{
	ULONGLONG StartCluster;
	NumberOfClusters;
	std::cout << "Enter start cluster: ";
	std::cin >> StartCluster;
	std::cout << "Enter count of clusters: ";
	std::cin >> NumberOfClusters;
	DWORD bufferSize = NumberOfClusters * fs->GetBytesPerCluster();
	BYTE * databuffer = new BYTE[bufferSize];
	fs->ReadClusters(StartCluster, NumberOfClusters, databuffer);
	fs->Print();
}

void Factory::ShowInfo(FileSystem * fs)
{
	std::cout << "OEM:" << fs->GetOem() << std::endl;
	std::cout << "Total clusters:" << fs->GetTotalClusters() << std::endl;
	std::cout << "Bytes in Cluster:" << fs->GetBytesPerCluster() << std::endl;
}

void Factory::Close(FileSystem * fs)
{
	fs->Close();
}

Iterator * Factory::GetIterator(FileSystem * fs)
{
	Iterator *it = new Iterator(fs);
	return it;
}

Factory::Factory()
{
}


Factory::~Factory()
{
}
