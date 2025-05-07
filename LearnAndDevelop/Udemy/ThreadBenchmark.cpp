#include "ThreadBenchmark.h"
#include "Worker.h"
#include <iostream>
#include <functional>
using namespace std;

void ThreadBenchmark::startMain(std::function<void()> mainTask)
{
	counter = 0;
	auto start = std::chrono::steady_clock::now();
	
	mainTask();

	cout << endl << "counter = " << counter << endl;
	auto end = std::chrono::steady_clock::now();
	chrono::milliseconds elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	cout << "Elapsed time: " << elapsed.count() << " ms\n";
}

void ThreadBenchmark::Task1()
{
	for (int i = 0; i < 100000; i++)
	{
		std::thread thrd(&ThreadBenchmark::incrementCounter, this);
		thrd.join();
	}
}
void ThreadBenchmark::Task2()
{
	Worker worker;
	for (int i = 0; i < 100000; i++)
	{
		function<void()> fun = bind(&ThreadBenchmark::incrementCounter, this);
		worker.add(fun);
		worker.joinFinishedUntilFirstRunning(500);
	}
	worker.joinAll();
}

void ThreadBenchmark::incrementCounter()
{
	lock_guard<mutex> lock(mtx);
	++counter;
}