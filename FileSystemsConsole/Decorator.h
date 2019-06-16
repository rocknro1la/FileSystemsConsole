#pragma once
#include "Iterator.h"
class Decorator :
	public Iterator
{
protected:
	Iterator *iterator;
	FileSystem* fs;
public:
	Decorator(Iterator *it);
	void First();
	void Next();
	bool IsDone();
	void Print();
	long CurrentOffset();
	~Decorator();
};

