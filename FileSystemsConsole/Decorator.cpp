#include "pch.h"
#include "Decorator.h"

Decorator::Decorator(Iterator * it):Iterator(NULL)
{
	iterator = it;
	fs = iterator->Fs;
}

void Decorator::First()
{
	iterator->First();

}

void Decorator::Next()
{
	if (!iterator->IsDone()) {
		bool doNext = true;
		while (doNext)
		{
			BYTE* DataBuffer = new BYTE[fs->GetBytesPerCluster()];
			fs->ReadClusters(iterator->CurrentOffset(), 1, DataBuffer);
			if (int(DataBuffer[0]) == 255 && int(DataBuffer[1]) == 216) {
				doNext = false;
			}			
			iterator->Next();
			delete DataBuffer;
		}
	}
}

bool Decorator::IsDone()
{
	return iterator->IsDone();
}

void Decorator::Print()
{
	iterator->Print();
}

long Decorator::CurrentOffset()
{
	return iterator->CurrentOffset();
}

Decorator::~Decorator()
{
}
