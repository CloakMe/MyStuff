#pragma once
#include <functional>
#include <mutex>

class MutexUsage
{
public :
	void runTwoJobs(std::function<void(int, std::mutex&)> job1, std::function<void(double, std::mutex&)> job2) const;
};

