#include "Resource.h"

#include <iostream>
#include "windows.h"
#define _CRTDBG_MAP_ALLOC //to get more details
#include <stdlib.h>  
#include <crtdbg.h>   //for malloc and free
#include "PerfectForwarding.h"

using namespace std;

int main()
{
	cout << "hello world Resource" << endl;
	_CrtMemState sOld;
	_CrtMemState sNew;
	_CrtMemState sDiff;
	_CrtMemCheckpoint(&sOld); //take a snapshot
	
	int x = 5;
	int * pX = &x;
	int & rX = x;
	ForwardAB(x, &x, rX, pX);

	RuleOfFive();

	OutputDebugString("hi");
	_CrtMemCheckpoint(&sNew); //take a snapshot 
	if (_CrtMemDifference(&sDiff, &sOld, &sNew)) // if there is a difference
	{
		OutputDebugString("-----------_CrtMemDumpStatistics ---------");
		_CrtMemDumpStatistics(&sDiff);
		OutputDebugString("-----------_CrtMemDumpAllObjectsSince ---------");
		_CrtMemDumpAllObjectsSince(&sOld);
		OutputDebugString("-----------_CrtDumpMemoryLeaks ---------");
		_CrtDumpMemoryLeaks();
	}
	return 0;
}

