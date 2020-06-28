#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include "CommandTest.h"
#include "BufferTest.h"
#include "TimerTest.h"
#include "CommandControllerTest.h"

#ifdef _DEBUG
#define new new( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define new new
#endif

int main() {
	cout << "[Testing Command]" << endl;
	CommandTest::Run();
	cout << endl << "[Testing Buffer]" << endl;
	BufferTest::Run();
	cout << endl << "[Testing Timer]" << endl;
	TimerTest::Run();
	cout << endl << "[Testing Command Controller]" << endl;
	CommandControllerTest::Run();

	delete[] COMMAND_TYPE_CONVERSIONS;
	delete[] COMMAND_ACTION_CONVERSIONS;

	_CrtDumpMemoryLeaks();

	return 0;
}