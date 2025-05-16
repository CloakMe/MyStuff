#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <atomic>

#include <functional>

#include "FizzBuzz.h"
#include "ThreadBenchmark.h"
#include "ConcurentStructuresModifier.h"

using namespace std;


class some_type 
{
public:
	void do_it() { }
};

atomic<some_type*> ptr{ nullptr };            // Variable to be lazily initialized
mutex process_mutex;

void process() {
	if (!ptr) {                     // First check of ptr
		lock_guard<mutex> lk(process_mutex);

		if (!ptr)                  // Second check of ptr
			ptr = new some_type;   // Initialize ptr
		cout << ptr.load() << endl;
	}
	ptr.load()->do_it();	
}


int main()
{
	char in;
	do
	{
		cout << "Please choose\n1 for FizzBuzz game\n"
			"2 for executing IncrementTask on many threads\n"
			"3 for Lazy Initialization\n"
			"4 for Concurent access inside elements of std::forward_list\n";
		cin >> in;

	} while (in < '1' || '4' < in);
	
	if (in == '1')
	{
		FizzBuzz game;

		thread thread(&FizzBuzz::PlayGame, &game, 20);
		thread.join();
		cout << game.GetResult();
	}
	else if (in == '2')
	{
		ThreadBenchmark threadBenchmark;
		function<void()> task1 = bind(&ThreadBenchmark::Task1, &threadBenchmark);
		function<void()> task2 = bind(&ThreadBenchmark::Task2, &threadBenchmark);
		threadBenchmark.startMain(task1);
		threadBenchmark.startMain(task2);
	}
	else if (in == '3')
	{
		thread thr1{ process };
		thread thr2{ process };

		thr1.join();
		thr2.join();
	}
	else if (in == '4')
	{
		using CSM = ConcurentStructuresModifier;

		runThreads(CSM(), &CSM::modifyEl1, &CSM::readEl2, 100);
		runThreads(CSM(), &CSM::removeEl1, &CSM::readEl2);
		runThreads(CSM(), &CSM::removeEl2, &CSM::readEl1);
		runThreads(CSM(), &CSM::removeEl1, &CSM::removeEl2);
		runThreads(CSM(), &CSM::removeEl2, &CSM::removeEl1);
		runThreads(CSM(), &CSM::removeEl2, &CSM::removeEl5);
	}

	return 0;
}