// MultiThreading.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <mutex>
#include "MutexUsage.h"
#include "LatchUsage.h"
#include "BarrierUsage.h"
#include "CondVariable.h"
#include "FutureUsage.h"

using namespace std;

static void display(int i, std::mutex& mutex)
{
	mutex.lock();
	i++;
	std::cout << "i = " << i << "!\n";
	mutex.unlock();
}

static void display(double d, std::mutex& mutex)
{
	mutex.lock();
	d = d * d;
	std::cout << "d = " << d << "!\n";
	mutex.unlock();
}

int main()
{
	std::cout << "Hello World!\n";
	MutexUsage mutexUsage;
	mutexUsage.runTwoJobs(
		static_cast<void(*)(int, std::mutex&)>(display), 
		static_cast<void(*)(double, std::mutex&)>(display));

	mutexUsage.runAJob();
	mutexUsage.runAJobUsingJthread();

	LatchUsage latchUsage;
	latchUsage.runTwoJobs();

	BarrierUsage barrierUsage;
	barrierUsage.runTwoJobs();

	CondVariable condVarUsage;
	thread thr2(&CondVariable::Read, &condVarUsage);
	thread thr1(&CondVariable::Write, &condVarUsage, "ho");
	
	thread thr4(&CondVariable::Write, &condVarUsage, "-ho");
	thread thr5(&CondVariable::Write, &condVarUsage, "-ho, Santa is here!");
	thread thr3(&CondVariable::Read, &condVarUsage);

	thr1.join();
	thr2.join();
	
	thr4.join();
	thr5.join();
	thr3.join();

	FutureUsage futureUsage;
	futureUsage.RunTwoJobs();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
