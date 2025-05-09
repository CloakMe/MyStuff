#include "Resource.h"

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include "windows.h"
#define _CRTDBG_MAP_ALLOC //to get more details
#include <stdlib.h>  
#include <crtdbg.h>   //for malloc and free
#include "PerfectForwarding.h"

using namespace std;
using namespace literals::chrono_literals;
void showType(int* val)
{
	cout << "Type of x*: " << typeid(val).name() << endl;
}
void showType(int val)
{
	cout << "Type of x: " << typeid(val).name() << endl;
}

int main()
{
	cout << "hello world Resource" << endl;
	_CrtMemState sOld;
	_CrtMemState sNew;
	_CrtMemState sDiff;
	_CrtMemCheckpoint(&sOld); //take a snapshot
	
	//universal initialization
	int x{ 5 };
	int y{ 7 };
	vector<int> vec{ 4,3,2,5,1 };
	for (auto elem : vec)
		cout << elem << endl;
	string str{ "Let us begin" };

	//perfect forwarding
	int * pX = &x;
	int & rX = x;
	ForwardAB(x, &x, rX, pX);

	//auto
	auto strIter = str.begin();
	string::iterator strIter2 = str.begin();
	const int& xref = rX;
	
	auto xrefAuto = xref; //const and ref are dropped
	rX = 10;

	//nullptr
	showType(pX);
	showType(x);
	showType(NULL);
	showType(nullptr);

	//chrono
    chrono::seconds two_sec(2), two_sec_new = 2s;
    chrono::milliseconds twenty_ms(20), twenty_ms_new = 20ms;
    chrono::microseconds fifty_mics(50), fifty_mics_new = 50us;


	//rule of five
	RuleOfFive();

	//detect memory leaks for rule of five
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

