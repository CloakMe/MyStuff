#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <atomic>

#include <functional>

#include "FizzBuzz.h"
#include "ThreadBenchmark.h"
#include "ConcurentStructuresModifier.h"
#include "Monitor.h"

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
			"4 for Concurent access inside elements of std::forward_list\n"
			"5 for Monitor class\n"
			"6 for Generic Monitor class\n"
			"7 for ThreadPool class\n";
		cin >> in;

	} while (in < '1' || '6' < in);
	
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
	else if (in == '5')
	{
		Monitor monitor;
		monitor.add_user("ivan", 500.0);
		monitor.add_user("georgi", 1500.51);

		thread thr1{ &Monitor::credit , &monitor, "ivan", 20 };
		thread thr2{ &Monitor::debit, &monitor, "georgi", 100.0 };
		thread thr3{ &Monitor::add_user, &monitor, "stavri", 50.0 };

		thr1.join();
		thr2.join();

		thread thr4{ &Monitor::show, &monitor, "ivan" };
		thread thr5{ &Monitor::show, &monitor, "georgi" };
		thread thr6{ &Monitor::show, &monitor, "stavri" };

		thr3.join();
		thr4.join();
		thr5.join();
		thr6.join();

		BankMonitor bankMonitor;
		bankMonitor.add_user("genadii", 500.0);

		thread thrr1{ &BankMonitor::credit , &bankMonitor, "genadii", 20 };
		thread thrr2{ &BankMonitor::debit, &bankMonitor, "genadii", 100.0 };
		thread thrr3{ &BankMonitor::show, &bankMonitor, "genadii" };

		thrr1.join();
		thrr2.join();
		thrr3.join();
	}
	else if (in == '6')
	{
		MonitorT<Bank> monT;
		auto job1 = [](Bank& bank)
		{
			bank.add_user("gesh", 111.1);
		};
		thread thr1{ [&monT, job1]()
			{
				monT(job1);
			}
		};
		auto job2 = [](Bank& bank)
		{
			bank.add_user("todor", 2222.2);
		};
		thread thr2{
			[&monT, job2]() { monT(job2); }
		};

		thr1.join();
		thr2.join();

		auto job3 = [](Bank& bank)
		{
			bank.debit("todor", 111.1);
			bank.credit("gesh", 111.1);
		};
		thread thr3{ 
			[&monT, job3]() { monT(job3); }
		};
		thr3.join();
	}
	else if (in == '7')
	{
		MonitorT<Bank> monT;
		auto job1 = [](Bank& bank)
		{
			bank.add_user("gesh", 111.1);
		};
		thread thr1{ [&monT, job1]()
			{
				monT(job1);
			}
		};
		auto job2 = [](Bank& bank)
		{
			bank.add_user("todor", 2222.2);
		};
		thread thr2{
			[&monT, job2]() { monT(job2); }
		};

		thr1.join();
		thr2.join();

		auto job3 = [](Bank& bank)
		{
			bank.debit("todor", 111.1);
			bank.credit("gesh", 111.1);
		};
		thread thr3{
			[&monT, job3]() { monT(job3); }
		};
		thr3.join();
	}

	return 0;
}