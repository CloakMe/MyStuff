// Thread pool with single queue
#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include "ThreadPool.h"
#include "ThreadQueue.h"
#include <thread>
#include <functional>

// Type alias to simplify the code
// All the task functions will have this type
using Func = std::function<void()>;

class ThreadPool
{
	// Queue of task functions
	ThreadQueue<Func> work_queue;

	// Vector of thread objects which make up the pool
	std::vector<std::thread> threads;

	// Entry point function for the threads
	void worker();

	// The number of threads in the pool
	int thread_count;
public:
	ThreadPool();
	~ThreadPool();

	// Add a task to the queue
	void submit(Func func);
};

#endif //THREAD_POOL_H