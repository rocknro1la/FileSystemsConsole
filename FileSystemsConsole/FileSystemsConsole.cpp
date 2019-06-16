// FileSystemsConsole.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include "Factory.h"
#include "FileSystem.h"
#include "Iterator.h"
#include "Decorator.h"

int main()
{	
	Factory *factory = new Factory();
	FileSystem *fs = factory->CreateFileSystem();
	factory->ShowInfo(fs);
	//factory->ShowFileSystem(fs);
	Decorator *dec = new Decorator(factory->GetIterator(fs));
	for (dec->First(); !dec->IsDone(); dec->Next()) {
		std::cout << "Cluster starts" << std::endl;
		dec->Print();
		std::cout << "Cluster ends" << std::endl;
	}
	factory->Close(fs);
}
