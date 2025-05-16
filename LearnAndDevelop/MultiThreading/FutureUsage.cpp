#include <iostream>
#include <chrono>
#include <future>
#include <thread>
#include "FutureUsage.h"
using namespace std;
using namespace literals;

void FutureUsage::RunTwoJobs()
{
	promise<int> promise;
	auto job1 = [&promise](int a, int b) {
		cout << "adding " << a << " and " << b << endl;
		std::this_thread::sleep_for(2s);
		promise.set_value(a + b);
	};

	future<int> fut = promise.get_future();
	auto job2 = [](future<int> future) {
		std::this_thread::sleep_for(20ms);
		cout << "result is " << future.get() << endl;
	};

	thread thr1(job1, 6, 7);
	thread thr2(job2, move(fut));

	thr1.join();
	thr2.join();
}

//
//int main() {
//	// Packaged task object
//	// The callable object is a lambda expression
//	// It takes int and int arguments
//	// It returns int
//	std::packaged_task<int(int, int)> ptask([](int a, int b) {
//		std::this_thread::sleep_for(2s);
//		return a + b;
//	});
//
//	// The promise object is an std::promise<int>
//	// Get the future associated with it
//	auto fut = ptask.get_future();
//
//	// Start a new thread
//	// The packaged task will be its entry point
//	std::thread thr(std::move(ptask), 6, 7);
//
//	std::cout << "Waiting for result\n";
//
//	std::cout << "6 + 7 is " << fut.get() << '\n';
//
//	thr.join();
//}