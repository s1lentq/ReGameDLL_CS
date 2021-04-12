#include "precompiled.h"
#include "cppunitlite/MainAdapter.h"

int main(int argc, char *argv[])
{
	printf("TestRunner: main()\n");

	MainAdapter a;
	return a.testsEntryPoint(argc, argv);
}
