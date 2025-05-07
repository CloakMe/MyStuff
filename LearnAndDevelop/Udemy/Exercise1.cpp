#include <iostream>
#include <string>
#include <thread>
#include <mutex>

#include <functional>

#include "FizzBuzz.h"
#include "ThreadBenchmark.h"

using namespace std;

//mutex mtx;
//int counter = 0;
//void incrementCounter()
//{
//	lock_guard<mutex> lock(mtx);
//	++counter;
//}

int main()
{
	FizzBuzz game;
	
	thread thread(&FizzBuzz::PlayGame, &game, 20);
	thread.join();
	cout << game.GetResult();

	ThreadBenchmark threadBenchmark;
	function<void()> task1 = bind(&ThreadBenchmark::Task1, &threadBenchmark);
	function<void()> task2 = bind(&ThreadBenchmark::Task2, &threadBenchmark);
	threadBenchmark.startMain(task1);
	threadBenchmark.startMain(task2);
	//threadBenchmark.startMain(bind(&ThreadBenchmark::Task2, threadBenchmark));
	/*auto start = std::chrono::steady_clock::now();

	for (int i = 0; i < 100000; i++)
	{
		std::thread thrd(&incrementCounter);
		thrd.join();
	}

	cout << endl << "counter = " << counter << endl;
	auto end = std::chrono::steady_clock::now();
	chrono::milliseconds elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	cout << "Elapsed time1: " << elapsed.count() << " ms\n";

	counter = 0;
	start = std::chrono::steady_clock::now();
	Worker worker;
	for (int i = 0; i < 100000; i++)
	{
		function fun(&incrementCounter);
		worker.add(fun);
		worker.joinFinishedUntilFirstRunning(500);
	}
	worker.joinAll();
	cout << endl << "counter = " << counter << endl;
	end = std::chrono::steady_clock::now();
	elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	cout << "Elapsed time2: " << elapsed.count() << " ms\n";*/

	return 0;
}