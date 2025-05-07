#pragma once
#include <functional>
#include <mutex>

class ThreadBenchmark
{
public:
	void startMain(std::function<void()> mainTask);

	void Task1();
	void Task2();
private:
	void incrementCounter();
	std::mutex mtx;
	int counter;
};

