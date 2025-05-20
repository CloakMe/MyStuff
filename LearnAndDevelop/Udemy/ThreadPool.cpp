// Thread pool with single queue
#include <iostream>
#include "ThreadPool.h"

// Constructor
ThreadPool::ThreadPool() {
	thread_count = std::thread::hardware_concurrency() - 1;
	std::cout << "Creating a thread pool with " << thread_count << " threads\n";

	// Start the threads
	for (int i = 0; i < thread_count; ++i)
		threads.push_back(std::thread{ &ThreadPool::worker, this });
}

// Destructor
ThreadPool::~ThreadPool() {
	// Wait for the threads to finish
	for (auto& thr : threads) {
		thr.join();
	}
}

// Entry point function for the threads
void ThreadPool::worker() {
	while (true) {
		Func task;

		// Take a task function off the queue
		work_queue.wait_and_pop(task);

		// Invoke it
		task();
	}
}

// Add a task to the queue
void ThreadPool::submit(Func func) {
	work_queue.push(std::move(func));
}
