#pragma once
#include "FileSystem.h"
class Iterator
{
protected:
	ULONGLONG clusterOffset;
public:
	FileSystem *Fs;
	Iterator(FileSystem *fs);
	void First();
	void Next();
	bool IsDone();
	long CurrentOffset();
	void Print();
	~Iterator();
};

