#pragma once
#include <functional>
#include <atomic>

#include "ThreadQueue.h"

class Worker
{
public:
	void add(std::function<void()>);
	void joinFinishedUntilFirstRunning(int threshold);
	void joinAll();
private:
	ThreadQueue<std::future<void>> m_queue;
};

