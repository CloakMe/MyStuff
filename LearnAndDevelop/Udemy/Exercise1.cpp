#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <atomic>

#include <functional>

#include "FizzBuzz.h"
#include "ThreadBenchmark.h"

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
		cout << "Please choose\n1 for FizzBuzz game\n2 for executing IncrementTask on many threads\n3 for Lazy Initialization\n";
		cin >> in;

	} while (in < '1' || '3' < in);
	
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
	

	return 0;
}