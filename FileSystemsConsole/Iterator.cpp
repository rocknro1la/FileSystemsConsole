#include "pch.h"
#include "Iterator.h"


Iterator::Iterator(FileSystem *fs)
{
	Fs = fs;
}

void Iterator::First()
{
	clusterOffset = 0;
}

void Iterator::Next()
{
	clusterOffset++;
}

bool Iterator::IsDone()
{
	if (clusterOffset >= Fs->GetTotalClusters()) {
		return true;
	}
	else {
		return false;
	}
}

long Iterator::CurrentOffset()
{
	return clusterOffset;
}

void Iterator::Print()
{
	Fs->Print();
}

Iterator::~Iterator()
{
}
