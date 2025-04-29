#include <iostream>
#include <mutex>
#include "MutexUsage.h"
#include "LatchUsage.h"
#include "BarrierUsage.h"
using namespace std;

static void display(int i, std::mutex& mutex)
{
	mutex.lock();
	i++;
	cout << "i = " << i << "!\n";
	mutex.unlock();
}

static void display(double d, std::mutex& mutex)
{
	mutex.lock();
	d = d * d;
	cout << "d = " << d << "!\n";
	mutex.unlock();
}

int main()
{
	std::cout << "Hello World!\n";
	MutexUsage mutexUsage;
	mutexUsage.runTwoJobs(
		static_cast<void(*)(int, std::mutex&)>(display), 
		static_cast<void(*)(double, std::mutex&)>(display));
	mutexUsage.runAJobUsingJthread();
	mutexUsage.runAJob();
		
	LatchUsage latchUsage;
	latchUsage.runTwoJobs();

	BarrierUsage barrierUsage;
	barrierUsage.runTwoJobs();
	return 0;
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
